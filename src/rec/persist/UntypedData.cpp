#include "rec/persist/UntypedData.h"
#include "rec/base/scoped_ptr.h"
#include "rec/persist/Copy.h"
#include "rec/proto/Proto.h"
#include "rec/util/STL.h"

namespace rec {
namespace persist {

using rec::proto::Operation;

UntypedData::UntypedData(const File& file, Message* message, AppBase* app)
    : file_(file),
      message_(message),
      app_(app) {
  if (!copy(file, message))
    LOG(ERROR) << "New file " << file.getFullPathName().toCString();
}

UntypedData::~UntypedData() {
  stl::deletePointers(&queue_);
  stl::deletePointers(&undo_);
}

template <typename Proto>
void UntypedData::change(Operation* op) {
  {
    ScopedLock l(lock_);
    queue_.push_back(op);
  }
  app_->needsUpdate(this);
}

void UntypedData::upate() {
  {
    ScopedLock l(lock_);
    if (queue_.empty())
      return;

    for (OperationList::iterator i = queue_.begin(); i != queue_.end(); ++i)
      undo_.push_back(proto::applyOperation(**i), message_);

    stl::deletePointers(&queue_);
  }

  changeCallback();
}

void UntypedData::write() {
  scoped_ptr<Message> msg;
  {
    ScopedLock l(lock_);
    if (!needsWrite_)
      return;

    msg.reset(message_->New());
    msg.reset(clone());
    needsWrite_ = false;
  }

  copy(*msg, _file_);
}

}  // namespace persist
}  // namespace rec
