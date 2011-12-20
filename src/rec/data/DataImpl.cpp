#include <google/protobuf/message.h>

#include "rec/data/DataImpl.h"
#include "rec/data/DataOps.h"
#include "rec/util/Copy.h"
#include "rec/util/Proto.h"

namespace rec {
namespace data {

DataImpl::DataImpl(Message *m, const File& file, DataUpdater* u, UndoStack* s)
    : Data(NULL), file_(file), dataUpdater_(u), undoStack_(s) {
  ptr<Message> original(m);
  message_.reset(m->New());
  fileReadSuccess_ = copy::copy(file_, message_.get());
  if (!fileReadSuccess_)
    message_.swap(original);
}

void DataImpl::pushOnUndoStack(const Message& before) {
  undoStack_->push(this, before, *message_);
}

void DataImpl::reportChange() {
  {
    Lock l(lock_);
    clientsNeedUpdate_ = true;
  }
  dataUpdater_->reportChange(this);
}

bool DataImpl::writeToFile() {
  ptr<Message> m;
  {
    Lock l(lock_);
    if (!alreadyReadFromFile_)
      return false;
    m.reset(clone(*message_));
  }

  return copy::copy(*m, file_);
}

void DataImpl::addListener(Listener<const Message&>* lis) {
  Lock l(broadcasterLock_);
  Data::addListener(lis);
  recentListeners_.insert(lis);
}

void DataImpl::removeListener(Listener<const Message&>* lis) {
  Lock l(broadcasterLock_);
  Data::addListener(lis);
  recentListeners_.erase(lis);
}

bool DataImpl::update() {
  ptr<Message> m;
  ListenerSet toUpdate;
  {
    Lock l(broadcasterLock_);
    if (clientsNeedUpdate_)
      recentListeners_.clear();
    else if (!recentListeners_.empty())
      toUpdate.swap(recentListeners_);
    else
      return false;
  }

  bool clientsNeedUpdate;
  {
    Lock l(lock_);
    m.reset(clone(*message_));
    clientsNeedUpdate = clientsNeedUpdate_;
    clientsNeedUpdate_ = false;
  }

  if (clientsNeedUpdate) {
    broadcast(*m);
  } else {
    for (ListenerSet::iterator i = toUpdate.begin(); i != toUpdate.end(); ++i)
      (**i)(*m);
  }

  return true;
}

void DataImpl::clearRecentListeners() {
  Lock l(lock_);
  recentListeners_.clear();
}

}  // namespace data
}  // namespace rec
