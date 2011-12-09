#include "rec/data/UntypedEditable.h"

#include "rec/data/EditableUpdater.h"
#include "rec/data/proto/Field.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/util/Copy.h"
#include "rec/data/Data.h"
#include "rec/data/Value.h"
#include "rec/util/STL.h"

namespace rec {
namespace data {

UntypedEditable::UntypedEditable(const File& file, const VirtualFile& vf,
                                 Message* message)
    : file_(file),
      virtualFile_(vf),
      message_(message),
      alreadyReadFromFile_(false),
      fileReadSuccess_(false) {
}

UntypedEditable::~UntypedEditable() {
  stl::deletePointers(&queue_);
}

MessageField UntypedEditable::createMessageField(const Address& a) const {
  return data::createMessageField(a, *message_);
}

bool UntypedEditable::hasValue(const Address& a) const {
  Lock l(lock_);
  return data::hasValue(createMessageField(a));
}

const Value UntypedEditable::getValue(const Address& a) const {
  Value value;
  Lock l(lock_);
  if (!data::copyTo(createMessageField(a), &value)) {
    LOG(DFATAL) << "Couldn't read value for " << a.ShortDebugString()
                << ", " << message_->ShortDebugString();
  }
  return value;
}

int UntypedEditable::getSize(const Address& address) const {
  Lock l(lock_);
  return data::getSize(createMessageField(address));
}

void UntypedEditable::copyTo(Message* message) const {
  Lock l(lock_);
  message->CopyFrom(*message_);
}

Message* UntypedEditable::clone() const {
  Lock l(lock_);
  if (message_) {
    ptr<Message> m(message_->New());
    copyTo(m.get());
    return m.transfer();
  }
  return NULL;
}

bool UntypedEditable::readFromFile() const {
  Lock l(lock_);
  if (!alreadyReadFromFile_) {
    fileReadSuccess_ = copy::copy(file_, message_);
    alreadyReadFromFile_ = true;
  }
  return fileReadSuccess_;
}

void UntypedEditable::applyLater(Operations* op) {
  {
    Lock l(lock_);
    queue_.push_back(op);
  }
  needsUpdate();
}

void UntypedEditable::needsUpdate() {
  EditableUpdater::instance()->needsUpdate(this);
}

void UntypedEditable::applyOperations(const Operations& olist,
                                      Operations* undoes) {
  if (undoes)
    undoes->Clear();

  Operation undo;
  for (int i = 0; i < olist.operation_size(); ++i) {
    const Operation& op = olist.operation(i);
    Lock l(lock_);
    if (undoes) {
      undo.Clear();
      undo.set_command(Operation::SET);
      undo.add_value()->CopyFrom(Value(*message_));
    }

    if (!data::apply(createMessageField(op.address()), op)) {
      LOG(DFATAL) << "Couldn't perform operation " << op.DebugString()
                  << "\n --> " << message_->ShortDebugString();
    } else if (undoes) {
      undoes->add_operation()->CopyFrom(undo);
    }
  }
}

bool UntypedEditable::update() {
  OperationList command;
  {
    Lock l(lock_);
    if (queue_.empty())
      return false;

    command.swap(queue_);
  }

  Operations undo;
  for (OperationList::iterator i = command.begin(); i != command.end(); ++i) {
    Lock l(lock_);
    applyOperations(**i, &undo);
    EditableUpdater::instance()->undoQueue()->add(this, **i, undo);
  }

  stl::deletePointers(&command);

  {
    ptr<Message> msg(clone());
    broadcaster_.broadcast(*msg);
  }
  onDataChange();
  return true;
}

bool UntypedEditable::writeToFile() const {
  ptr<Message> msg;
  {
    Lock l(lock_);
    if (!alreadyReadFromFile_)
      return false;

    msg.reset(message_->New());
    msg->CopyFrom(*message_);
  }

	VLOG(1) << "Writing " << str(file_);
  return copy::copy(*msg, file_);
}

}  // namespace data
}  // namespace rec
