#include <glog/logging.h>

#include "rec/persist/UntypedData.h"
#include "rec/base/scoped_ptr.h"
#include "rec/persist/Copy.h"
#include "rec/persist/AppBase.h"
#include "rec/proto/Proto.h"
#include "rec/util/STL.h"

namespace rec {
namespace persist {

using rec::proto::Operation;

UntypedData::UntypedData(const File& file, Message* message, AppBase* app)
    : file_(file),
      message_(message),
      app_(app) {
}

void UntypedData::readFromFile() {
  if (!copy(file_, message_))
    LOG(ERROR) << "New file " << file_.getFullPathName().toCString();
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

    for (OperationList::iterator i = queue_.begin(); i != queue_.end(); ++i)
      undo_.push_back(proto::applyOperation(**i, message_));

    stl::deletePointers(&queue_);
  }

  changeCallback();
}

void UntypedData::writeToFile() {
  scoped_ptr<Message> msg;
  {
    ScopedLock l(lock_);
    msg.reset(message_->New());
    msg->CopyFrom(*message_);
  }

  copy(*msg, &file_);
}

}  // namespace persist
}  // namespace rec
