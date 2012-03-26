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

  DataSet toUpdate;
  updateData_.swap(toUpdate);

  if (toUpdate.empty())
    return false;

  DataSet toWrite;
  {
    ScopedUnlock u(lock_);
    int j = 0;
    for (DataSet::iterator i = toUpdate.begin(); i != toUpdate.end(); ++i, ++j) {
      Data* data = *i;
      if (data->update())
        toWrite.insert(data);
    }

    if (toWrite.empty())
      return false;
  }

  if (updateThread_->threadShouldExit())
    return false;

  writeData_.insert(toWrite.begin(), toWrite.end());
  if (writeThread_)
    writeThread_->notify();

  return true;
}

bool DataUpdater::write() {
  DataSet toWrite;
  {
    Lock l(lock_);
    if (!writeThread_)
      writeThread_ = Thread::getCurrentThread();

    if (writeThread_->threadShouldExit() || writeData_.empty())
      return false;

    writeData_.swap(toWrite);
  }

  for (DataSet::iterator i = toWrite.begin(); i != toWrite.end(); ++i) {
    if (writeThread_->threadShouldExit())
      return false;
    else
      (*i)->writeToFile();
  }

  return true;
}

}  // namespace data
}  // namespace rec
