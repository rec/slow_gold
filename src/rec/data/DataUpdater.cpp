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
  Lock l(updateLock_);
  updateData_.insert(data);
  if (updateThread_)
    updateThread_->notify();
}

bool DataUpdater::update() {
  DataSet toUpdate;
  Lock l(lock_);
  {
    Lock l2(updateLock_);
    if (!updateThread_)
      updateThread_ = Thread::getCurrentThread();

    updateData_.swap(toUpdate);
  }

  if (toUpdate.empty())
    return false;

  DataSet toWrite;
  int j = 0;
  for (DataSet::iterator i = toUpdate.begin(); i != toUpdate.end(); ++i, ++j) {
    Data* data = *i;
    if (data->update())
      toWrite.insert(data);
  }

  if (toWrite.empty())
      return false;

  Lock l2(writeLock_);
  writeData_.insert(toWrite.begin(), toWrite.end());
  if (writeThread_)
    writeThread_->notify();

  return true;
}

bool DataUpdater::hasUpdates() const {
  Lock l(updateLock_);
  return updateThread_ && !updateData_.empty();
}

bool DataUpdater::write() {
  DataSet toWrite;
  {
    Lock l2(writeLock_);
    if (!writeThread_)
      writeThread_ = Thread::getCurrentThread();

    if (writeData_.empty())
      return false;

    writeData_.swap(toWrite);
  }

  for (DataSet::iterator i = toWrite.begin(); i != toWrite.end(); ++i)
    (*i)->writeToFile();

  return true;
}

}  // namespace data
}  // namespace rec
