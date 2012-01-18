#include <set>

#include "rec/data/DataUpdater.h"

#include "rec/data/Data.h"
#include "rec/data/DataMap.h"
#include "rec/data/DataOps.h"
#include "rec/util/STL.h"

namespace rec {
namespace data {

// A piece of data got new information!
void DataUpdater::reportChange(Data* data) {
  {
    Lock l(lock_);
    updateData_.insert(data);
    if (updateThread_)
      updateThread_->notify();
  }
}

bool DataUpdater::update() {
  Lock l(lock_);

  if (!updateThread_)
    updateThread_ = Thread::getCurrentThread();

  if (updateThread_->threadShouldExit())
    return false;

  DataSet toUpdate, toWrite, toRemove;
  updateData_.swap(toUpdate);

  if (toUpdate.empty())
    return false;

  {
    ScopedUnlock u(lock_);
    for (DataSet::iterator i = toUpdate.begin(); i != toUpdate.end(); ++i) {
      Data* data = *i;
      if (!data->listenerSize())
        toRemove.insert(data);
      else if (data->update())
        toWrite.insert(data);
    }

    if (toWrite.empty() && toRemove.empty())
      return false;
  }

  if (updateThread_->threadShouldExit())
    return false;

  stl::moveTo(&toWrite, &writeData_);
  stl::moveTo(&toRemove, &removeData_);
  if (writeThread_)
    writeThread_->notify();

  return true;
}

bool DataUpdater::write() {
  DataSet toWrite, toRemove;
  {
    Lock l(lock_);
    if (!writeThread_)
      writeThread_ = Thread::getCurrentThread();

    if (writeThread_->threadShouldExit() ||
        (writeData_.empty() && removeData_.empty())) {
      return false;
    }

    writeData_.swap(toWrite);
    removeData_.swap(toRemove);
  }

  for (DataSet::iterator i = toWrite.begin(); i != toWrite.end(); ++i) {
    if (writeThread_->threadShouldExit())
      return false;
    else
      (*i)->writeToFile();
  }

  for (DataSet::iterator i = toRemove.begin(); i != toRemove.end(); ++i) {
    if (writeThread_->threadShouldExit())
      return false;
    else
      removeData(*i);
  }

  return true;
}

void DataUpdater::removeData(Data* data) {
  // DLOG(INFO) << "Removing data " << data->getTypeName() << ", " << data->key();
  // TODO: why doesn't this work?
  // map_->removeData(data);
}

}  // namespace data
}  // namespace rec
