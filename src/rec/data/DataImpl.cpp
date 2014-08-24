#include <google/protobuf/message.h>

#include "rec/data/DataImpl.h"
#include "rec/data/DataOps.h"
#include "rec/data/DataUpdater.h"
#include "rec/data/UndoStack.h"
#include "rec/util/Copy.h"
#include "rec/util/proto/Proto.h"

namespace rec {
namespace data {

DataImpl::DataImpl(Message *m, const File& file, DataUpdater* u, UndoStack* s,
                   bool isEmpty, const string& key)
    : Data(isEmpty), file_(file), dataUpdater_(u), undoStack_(s), key_(key) {
  ptr<Message> original(m);
  fileReadSuccess_ = false;

  if (!isEmpty) {
    message_.reset(m->New());
#ifndef SLOWGOLD_SAVE_DISABLED
    fileReadSuccess_ = copy::copy(file_, message_.get());
#endif
  }

  if (!fileReadSuccess_)
    message_.swap(original);
}

void DataImpl::reportChange() {
  // DLOG(INFO) << "Reporting change " << str(file_);
  dataUpdater_->reportChange(this);
}

const string DataImpl::toString() const {
  Lock l(lock_);
  return getTypeName() + ": " + message_->ShortDebugString();
}

#define CLONE() (*ptr<Message>(clone()))

void DataImpl::pushOnUndoStack(const Message& before) {
  undoStack_->push(this, before, CLONE());
}

bool DataImpl::writeToFile() {
#ifndef SLOWGOLD_SAVE_DISABLED
  if (isEmpty_) {
    LOG(DFATAL) << "Tried to write an empty value.";
    return false;
  }
  return copy::copy(CLONE(), file_);
#else
  return true;
#endif
}

void DataImpl::update() {
  broadcast(CLONE());
}

}  // namespace data
}  // namespace rec
