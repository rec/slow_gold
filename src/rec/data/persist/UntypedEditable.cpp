#include "rec/data/persist/UntypedEditable.h"

#include "rec/data/persist/Copy.h"
#include "rec/data/proto/Field.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/data/persist/Persist.h"
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
  ScopedLock l(lock_);
  return fillMessageField(&f, address, *message_) && data::hasValue(f);
}

const Value UntypedEditable::getValue(const Address& address) const {
  Value value;
  MessageField f;
  ScopedLock l(lock_);
  if (!(fillMessageField(&f, address, *message_) && proto::copyTo(f, &value)))
    LOG(ERROR) << "Couldn't read value for " << address.DebugString();
  return value;
}

int UntypedEditable::getSize(const Address& address) const {
  MessageField f;
  ScopedLock l(lock_);
  return fillMessageField(&f, address, *message_) ? 0 : data::getSize(f);
}

void UntypedEditable::copyTo(Message* message) const {
  ScopedLock l(lock_);
  message->CopyFrom(*message_);
}

Message* UntypedEditable::clone() const {
  ScopedLock l(lock_);
  if (message_) {
    ptr<Message> m(message_->New());
    copyTo(m.get());
    return m.transfer();
  }
  return NULL;
}

void UntypedEditable::readFromFile() const {
  ScopedLock l(lock_);
  if (!alreadyReadFromFile_) {
    fileReadSuccess_ = data::copy(file_, message_);
    if (fileReadSuccess_)
      VLOG(1) << "Opening data " << str(file_);
    else
      VLOG(1) << "New data " << str(file_);

    alreadyReadFromFile_ = true;
  }
}

void UntypedEditable::applyLater(Operations* op) {
  {
    ScopedLock l(lock_);
    queue_.push_back(op);
  }
  data::needsUpdate(this);
}

Operations* UntypedEditable::applyOperations(const Operations& olist) {
  ptr<Operations> result (new Operations());
  for (int i = 0; i < olist.operation_size(); ++i) {
    const Operation& op = olist.operation(i);
    MessageField f;
    ScopedLock l(lock_);
    if (!fillMessageField(&f, Address(op.address()), *message_)) {
      LOG(ERROR) << "Couldn't perform operation " << op.ShortDebugString();
      return NULL;
    }
    Operation undo;
    if (proto::undo(&f, op, &undo) && proto::apply(&f, op))
      result->add_operation()->CopyFrom(undo);
    else
      LOG(ERROR) << "Couldn't perform operation " << op.DebugString();
  }
  return result.transfer();
}

void UntypedEditable::update() {
  OperationList command;
  {
    ScopedLock l(lock_);
    if (queue_.empty())
      return;

    command.swap(queue_);
  }

  OperationList undo;
  for (OperationList::iterator i = command.begin(); i != command.end(); ++i) {
    ScopedLock l(lock_);
    undo.push_back(applyOperations(**i));
  }

  addToUndoQueue(this, command, undo);
  stl::deletePointers(&command);
  stl::deletePointers(&undo);
  onDataChange();
}

void UntypedEditable::writeToFile() const {
  ptr<Message> msg;
  {
    ScopedLock l(lock_);
    if (!alreadyReadFromFile_)
      return;
    msg.reset(message_->New());
    msg->CopyFrom(*message_);
  }

	VLOG(1) << "Writing " << str(file_);
  data::copy(*msg, file_);
}

}  // namespace data
}  // namespace rec
