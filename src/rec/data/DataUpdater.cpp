#include <set>

#include "rec/data/DataUpdater.h"

namespace rec {
namespace data {

// A piece of data got new information!
void DataUpdater::needsUpdate(Data* data) {
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

  DataSet toUpdate, toWrite;
  updateData_.swap(toUpdate);

  {
    ScopedUnlock u(lock_);
    for (DataSet::iterator i = toUpdate.begin(); i != toUpdate.end(); ++i) {
      if ((**i)->updateClients())
        toWrite.insert(*i);
    }

    if (toWrite.empty())
      return false;
  }

  stl::moveTo(&toWrite, writeData_);
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

    if (writeData_.empty())
      return false;

    writeData_.swap(toWrite);
  }

  for (DataSet::iterator i = ds.begin(); i != ds.end(); ++i)
    (*i)->writeToFile();

  return true;
}

}  // namespace data
}  // namespace rec
