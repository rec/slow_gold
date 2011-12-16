#include "rec/data/DataImpl.h"

namespace rec {
namespace data {

DataImpl::DataImpl(Message *m, DataUpdater* u, UndoStack* s)
    : Data(m), dataUpdater_(u), undoStack_(s) {
}

void DataImpl::pushOnUndoStack(const Message& before) {
  undoStack_->push(this, before, *message_);
}

void DataImpl::reportChange() const {
  {
    Lock l(lock_);
    clientsNeedUpdate_ = true;
  }
  dataUpdater_->reportChange(this);
}

void DataImpl::addListener(const Listener<const Message&>* lis) {
  Lock l(broadcasterLock_);
  Data::addListener(lis);
  recentListeners_.insert(lis);
}

void DataImpl::removeListener(const Listener<const Message&>* lis) {
  Lock l(broadcasterLock_);
  Data::addListener(lis);
  recentListeners_.remove(lis);
}

bool DataImpl::update() {
  ptr<Message> m;
  ListenerSet toUpdate;
  bool clientsNeedUpdate = false;
  {
    Lock l(broadcasterLock_);
    if (clientsNeedUpdate_)
      recentListeners_.clear();
    else if (!recentListeners_.empty())
      toUpdate.swap(recentListeners_);
    else
      return false;
  }

  {
    Lock l(lock_);
    m.reset(message_->New());
    m->CopyFrom(*message_)
    clientsNeedUpdate = clientsNeedUpdate_;
    clientsNeedUpdate_ = false;
  }

  if (clientsNeedUpdate) {
    broadcast(*m);
  } else {
    for (ListenerSet::iterator i = toUpdate.begin(); i != toUpdate.end(); ++i)
      (*i->second)(*m);
  }

  return true;
}

void DataImpl::clearRecentListeners() {
  Lock l(lock_);
  recentListeners_.clear();
}

}  // namespace data
}  // namespace rec
