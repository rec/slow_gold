#include "rec/data/persist/UntypedEditable.h"

#include "rec/data/persist/EditableFactory.h"
#include "rec/data/persist/EditableUpdateQueue.h"
#include "rec/data/persist/Copy.h"
#include "rec/data/proto/Field.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/Value.h"
#include "rec/util/STL.h"

#include "rec/data/proto/Proto.h"

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
  ScopedLock l(lock_);
  ptr<Field> f(Field::makeField(address, *message_));
  return f && f->hasValue();
}

const Value UntypedEditable::getValue(const Address& address) const {
  Value value;
  ScopedLock l(lock_);
  ptr<Field> f(Field::makeField(address, *message_));
  if (f)
    f->copyTo(&value);
  else
    LOG(ERROR) << "Couldn't read value for " << address.DebugString();
  return value;
}

int UntypedEditable::getSize(const Address& address) const {
  ScopedLock l(lock_);
  ptr<Field> f(Field::makeField(address, *message_));
  return f ? f->getSize() : 0;
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
    fileReadSuccess_ = persist::copy(file_, message_);
    if (fileReadSuccess_)
      VLOG(1) << "Opening data " << str(file_);
    else
      VLOG(1) << "New data " << str(file_);

    alreadyReadFromFile_ = true;
  }
}

void UntypedEditable::apply(OperationList* op) {
  {
    ScopedLock l(lock_);
    queue_.push_back(op);
  }
  persist::EditableUpdateQueue::needsUpdate(this);
}

void UntypedEditable::update() {
  OperationQueue old;
  {
    ScopedLock l(lock_);
    if (queue_.empty())
      return;

    old.swap(queue_);
  }

  OperationQueue undo;
  for (OperationQueue::iterator i = old.begin(); i != old.end(); ++i) {
    ScopedLock l(lock_);
    undo.push_back(applyOperations(**i, message_));
  }

  stl::deletePointers(&old);
  persist::EditableUpdateQueue::addToUndoQueue(this, &undo);
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

	LOG(INFO) << "Writing " << str(file_);
  persist::copy(*msg, file_);
}

}  // namespace data
}  // namespace rec
