#include <glog/logging.h>

#include "rec/data/persist/UntypedData.h"

#include "rec/data/persist/App.h"
#include "rec/data/persist/Copy.h"
#include "rec/data/proto/Proto.h"
#include "rec/util/STL.h"
#include "rec/data/proto/Setter.h"


namespace rec {
namespace persist {

using rec::proto::Operation;

UntypedData::UntypedData(const File& file, Message* message, App* app)
    : file_(new File(file)),
      message_(message),
      app_(app),
      alreadyReadFromFile_(false) {
  setter_.addListener(this);
}

void UntypedData::readFromFile() const {
  if (!alreadyReadFromFile_) {
    if (copy(*file_, message_))
      LOG(INFO) << "Opening data " << file_->getFullPathName().toCString();
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

void UntypedData::update() {
  {
    ScopedLock l(lock_);
    if (queue_.empty())
      return;

    for (OperationList::iterator i = queue_.begin(); i != queue_.end(); ++i)
      undo_.push_back(applyOperation(**i, message_));

    stl::deletePointers(&queue_);
  }

  changeCallback();
}

void UntypedData::writeToFile() const {
  scoped_ptr<Message> msg;
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
