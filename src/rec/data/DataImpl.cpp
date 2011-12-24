#include <google/protobuf/message.h>

#include "rec/data/DataImpl.h"
#include "rec/data/DataOps.h"
#include "rec/util/Copy.h"
#include "rec/util/Proto.h"

namespace rec {
namespace data {

DataImpl::DataImpl(Message *m, const File& file, DataUpdater* u, UndoStack* s,
                   bool isEmpty)
    : Data(isEmpty), file_(file), dataUpdater_(u), undoStack_(s) {
  if (isEmpty) {
    message_.reset(m);
  } else {
    ptr<Message> original(m);
    message_.reset(m->New());
    fileReadSuccess_ = copy::copy(file_, message_.get());
    if (!fileReadSuccess_)
      message_.swap(original);
  }
  typeName_ = getTypeName(*message_);
}

void DataImpl::pushOnUndoStack(const Message& before) {
  undoStack_->push(this, before, *message_);
}

void DataImpl::reportChange() {
  {
    Lock l(lock_);
    changed_ = true;
  }
  dataUpdater_->reportChange(this);
}

bool DataImpl::writeToFile() {
  if (isEmpty_) {
    LOG(ERROR) << "Tried to write an empty value.";
    return false;
  }
  ptr<Message> m;
  {
    Lock l(lock_);
    m.reset(clone(*message_));
  }

  return copy::copy(*m, file_);
}

void DataImpl::addListener(Listener<const Message&>* lis) {
  Lock l(broadcasterLock_);
  Data::addListener(lis);
  recentListeners_.insert(lis);
  dataUpdater_->reportChange(this);
}

void DataImpl::removeListener(Listener<const Message&>* lis) {
  Lock l(broadcasterLock_);
  Data::removeListener(lis);
  recentListeners_.erase(lis);
}

bool DataImpl::update() {
  if (isEmpty_) {
    LOG(ERROR) << "Tried to update an empty value.";
    return false;
  }
  ptr<Message> m;
  ListenerSet toUpdate;

  bool changed;
  {
    Lock l(lock_);
    changed = changed_;
    changed_ = false;
  }

  {
    Lock l(broadcasterLock_);
    if (changed)
      recentListeners_.clear();

    else if (!recentListeners_.empty())
      toUpdate.swap(recentListeners_);

    else
      return false;
  }

  {
    Lock l(lock_);
    DCHECK_EQ(typeName_, getTypeName(*message_));
    m.reset(clone(*message_));
  }

  if (changed) {
    broadcast(*m);
  } else {
    for (ListenerSet::iterator i = toUpdate.begin(); i != toUpdate.end(); ++i)
      (**i)(*m);
  }

  return changed;
}

void DataImpl::clearRecentListeners() {
  Lock l(lock_);
  recentListeners_.clear();
}

}  // namespace data
}  // namespace rec
