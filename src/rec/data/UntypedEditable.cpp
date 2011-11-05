#include "rec/data/UntypedEditable.h"

#include "rec/data/EditableUpdater.h"
#include "rec/data/proto/Field.h"
#include "rec/data/proto/MessageField.h"
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

bool UntypedEditable::hasValue(const Address& address) const {
  MessageField f;

  Lock l(lock_);
  return fillMessageField(&f, address, *message_) && data::hasValue(f);
}

const Value UntypedEditable::getValue(const Address& address) const {
  Value value;
  MessageField f;

  Lock l(lock_);
  if (!(fillMessageField(&f, address, *message_) && data::copyTo(f, &value)))
    LOG(ERROR) << "Couldn't read value for " << address.ShortDebugString();
  return value;
}

int UntypedEditable::getSize(const Address& address) const {
  MessageField f;
  Lock l(lock_);
  return fillMessageField(&f, address, *message_) ? 0 : data::getSize(f);
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
    fileReadSuccess_ = copy::copy(file_, message_, copy::READABLE);
    if (fileReadSuccess_)
      VLOG(1) << "Opening data " << str(file_);
    else
      VLOG(1) << "New data " << str(file_);

    alreadyReadFromFile_ = true;
  }
  return fileReadSuccess_;
}

void UntypedEditable::applyLater(Operations* op) {
  Lock l(lock_);
  queue_.push_back(op);
    EditableUpdater::instance()->needsUpdate(this);
}

Operations* UntypedEditable::applyOperations(const Operations& olist) {
  ptr<Operations> result(new Operations());
  for (int i = 0; i < olist.operation_size(); ++i) {
    const Operation& op = olist.operation(i);
    MessageField f;
    Lock l(lock_);
    if (!fillMessageField(&f, Address(op.address()), *message_)) {
      LOG(ERROR) << "Couldn't perform operation " << op.ShortDebugString();
      return NULL;
    }
    Operation undo;
    if (data::undo(&f, op, &undo) && data::apply(&f, op))
      result->add_operation()->CopyFrom(undo);
    else
      LOG(ERROR) << "Couldn't perform operation " << op.ShortDebugString();
  }
  return result.transfer();
}

bool UntypedEditable::update() {
  OperationList command;
  {
    Lock l(lock_);
    if (queue_.empty())
      return false;

    command.swap(queue_);
  }

  for (OperationList::iterator i = command.begin(); i != command.end(); ++i) {
    ptr<Operations> ops(*i);
    ptr<Operations> undo(applyOperations(*ops));
    EditableUpdater::instance()->undoQueue()->add(this, *ops, *undo);
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
  return copy::copy(*msg, file_, copy::READABLE);
}

}  // namespace data
}  // namespace rec
