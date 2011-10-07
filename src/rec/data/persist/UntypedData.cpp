#include "rec/data/persist/UntypedData.h"

#include "rec/data/persist/App.h"
#include "rec/data/persist/Copy.h"
#include "rec/data/proto/Proto.h"
#include "rec/util/STL.h"

namespace rec {
namespace data {

bool UntypedData::hasValue(const Address& address) const {
  ScopedLock l(lock_);
  return data::hasValue(address, *message_);
}

const Value UntypedData::getValue(const Address& address) const {
  ScopedLock l(lock_);
  return data::getValue(address, *message_);
}

int UntypedData::getSize(const Address& address) const {
  ScopedLock l(lock_);
  return data::getSize(address, *message_);
}

void UntypedData::copyTo(Message* message) const {
  ScopedLock l(lock_);
  message->CopyFrom(*message_);
}

UntypedData::UntypedData(const File& file, Message* message, persist::App* app)
    : file_(new File(file)),
      message_(message),
      app_(app),
      alreadyReadFromFile_(false),
      fileReadSuccess_(false) {
}

Message* UntypedData::clone() const {
  ScopedLock l(lock_);
  if (message_) {
    ptr<Message> m(message_->New());
    copyTo(m.get());
    return m.transfer();
  }
  return NULL;
}

void UntypedData::readFromFile() const {
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

UntypedData::~UntypedData() {
  stl::deletePointers(&queue_);
  stl::deletePointers(&undo_);
}

void UntypedData::operator()(OperationList* op) {
  {
    ScopedLock l(lock_);
    queue_.push_back(op);
  }
  app_->needsUpdate(this);
}

void UntypedData::requestUpdate() {
  (*this)(new OperationList);
}

void UntypedData::update() {
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

void UntypedData::writeToFile() const {
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
