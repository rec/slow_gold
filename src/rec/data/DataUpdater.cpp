#include <set>

#include "rec/data/DataUpdater.h"

#include "rec/data/Data.h"
#include "rec/data/DataMap.h"
#include "rec/data/DataOps.h"
#include "rec/data/DataSet.h"
#include "rec/util/STL.h"
#include "rec/util/HasLock.h"

namespace rec {
namespace data {

DataUpdater::DataUpdater()
  : map_(nullptr), update_(new DataSet), write_(new DataSet) {
}

DataUpdater::~DataUpdater() {}

// A piece of data got new information!
void DataUpdater::reportChange(Data* data) {
  update_->insert(data);
}

bool DataUpdater::update() {
  ptr<DataSet::Set> updates(update_->release());
  if (!updates)
    return false;
  for (DataSet::Set::iterator i = updates->begin(); i != updates->end(); ++i)
    (*i)->update();

  write_->insert(updates.release());
  return true;
}

bool DataUpdater::hasUpdates() const {
  return update_->hasUpdates();
}

bool DataUpdater::write() {
  ptr<DataSet::Set> toWrite(write_->release());
  if (toWrite) {
    for (DataSet::Set::iterator i = toWrite->begin(); i != toWrite->end(); ++i)
      (*i)->writeToFile();
  }

  return toWrite && !toWrite->empty();
}

}  // namespace data
}  // namespace rec
