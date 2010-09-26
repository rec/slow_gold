#include <glog/logging.h>

#include "rec/persist/UntypedData.h"

#include "rec/base/scoped_ptr.h"
#include "rec/persist/App.h"
#include "rec/persist/Copy.h"
#include "rec/proto/Proto.h"
#include "rec/util/STL.h"

namespace rec {
namespace persist {

using rec::proto::Operation;

UntypedData::UntypedData(const File& file, Message* message, App* app)
    : file_(file),
      message_(message),
      setter_(this),
      app_(app),
      alreadyReadFromFile_(false) {
}

void UntypedData::readFromFile() const {
  if (!alreadyReadFromFile_) {
    if (!copy(file_, message_))
      LOG(ERROR) << "New file " << file_.getFullPathName().toCString();
    alreadyReadFromFile_ = true;
  }
}

UntypedData::~UntypedData() {
  stl::deletePointers(&queue_);
  stl::deletePointers(&undo_);
}

void UntypedData::change(proto::Operation* op) {
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

    readFromFile();
    for (OperationList::iterator i = queue_.begin(); i != queue_.end(); ++i)
      undo_.push_back(proto::applyOperation(**i, message_));

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

  copy(*msg, const_cast<File*>(&file_));
}

}  // namespace persist
}  // namespace rec
