#include "rec/data/persist/UntypedData.h"

#include "rec/data/persist/App.h"
#include "rec/data/persist/Copy.h"
#include "rec/data/proto/Proto.h"
#include "rec/util/STL.h"
#include "rec/data/proto/Setter.h"

namespace rec {
namespace persist {

using rec::proto::Operation;

bool UntypedData::hasValue(const Address& address) const {
  return proto::hasValue(address, *message_);
}

const Value UntypedData::getValue(const Address& address) const {
  return proto::getValue(address, *message_);
}

int UntypedData::getSize(const Address& address) const {
  return proto::getSize(address, *message_);
}

UntypedData::UntypedData(const File& file, Message* message, App* app)
    : file_(new File(file)),
      message_(message),
      app_(app),
      alreadyReadFromFile_(false),
      fileReadSuccess_(false) {
}

void UntypedData::readFromFile() const {
  if (!alreadyReadFromFile_) {
    fileReadSuccess_ = copy(*file_, message_);
    if (fileReadSuccess_)
      DLOG(INFO) << "Opening data " << file_->getFullPathName().toCString();
    else
      LOG(ERROR) << "New data " << file_->getFullPathName().toCString();

    alreadyReadFromFile_ = true;
  }
}

UntypedData::~UntypedData() {
  stl::deletePointers(&queue_);
  stl::deletePointers(&undo_);
}

void UntypedData::operator()(proto::Operation* op) {
  {
    ScopedLock l(lock_);
    queue_.push_back(op);
  }
  app_->needsUpdate(this);
}

void UntypedData::requestUpdate() {
  (*this)((proto::Operation*)NULL);
}

void UntypedData::update() {
  OperationList oldQueue;
  {
    ScopedLock l(lock_);
    if (queue_.empty())
      return;

    oldQueue.swap(queue_);
  }

  for (OperationList::iterator i = oldQueue.begin(); i != oldQueue.end(); ++i) {
    if (*i) {
      ScopedLock l(lock_);
      undo_.push_back(applyOperation(**i, message_));
    }
  }

  stl::deletePointers(&oldQueue);
  changeCallback();
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

  copy(*msg, const_cast<File*>(file_.get()));
}

}  // namespace persist
}  // namespace rec
