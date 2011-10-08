#include "rec/data/persist/UntypedEditable.h"

#include "rec/data/persist/App.h"
#include "rec/data/persist/Copy.h"
#include "rec/data/proto/Proto.h"
#include "rec/util/STL.h"

namespace rec {
namespace data {

bool UntypedEditable::hasValue(const Address& address) const {
  ScopedLock l(lock_);
  return data::hasValue(address, *message_);
}

const Value UntypedEditable::getValue(const Address& address) const {
  ScopedLock l(lock_);
  return data::getValue(address, *message_);
}

int UntypedEditable::getSize(const Address& address) const {
  ScopedLock l(lock_);
  return data::getSize(address, *message_);
}

void UntypedEditable::copyTo(Message* message) const {
  ScopedLock l(lock_);
  message->CopyFrom(*message_);
}

UntypedEditable::UntypedEditable(const File& file, Message* message, persist::App* app)
    : file_(new File(file)),
      message_(message),
      app_(app),
      alreadyReadFromFile_(false),
      fileReadSuccess_(false) {
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
    fileReadSuccess_ = persist::copy(*file_, message_);
    if (fileReadSuccess_)
      VLOG(1) << "Opening data " << file_->getFullPathName();
    else
      VLOG(1) << "New data " << file_->getFullPathName();

    alreadyReadFromFile_ = true;
  }
}

UntypedEditable::~UntypedEditable() {
  stl::deletePointers(&queue_);
  stl::deletePointers(&undo_);
}

void UntypedEditable::apply(OperationList* op) {
  {
    ScopedLock l(lock_);
    queue_.push_back(op);
  }
  app_->needsUpdate(this);
}

void UntypedEditable::update() {
  OperationQueue old;
  {
    ScopedLock l(lock_);
    if (queue_.empty())
      return;

    old.swap(queue_);
  }

  for (OperationQueue::iterator i = old.begin(); i != old.end(); ++i) {
    ScopedLock l(lock_);
    undo_.push_back(applyOperations(**i, message_));
  }

  stl::deletePointers(&old);
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

  persist::copy(*msg, const_cast<File*>(file_.get()));
}

}  // namespace data
}  // namespace rec