#include <set>

#include "rec/data/DataUpdater.h"

#include "rec/data/Data.h"
#include "rec/data/DataMap.h"
#include "rec/data/DataOps.h"
#include "rec/util/STL.h"
#include "rec/util/HasLock.h"

namespace rec {
namespace data {

class DataUpdater::DataSet : public HasLock {
 public:
  DataSet() : thread_(NULL) {}

  typedef std::set<Data*> Set;

  Set* transfer() {
    Lock l(lock_);
    if (!thread_)
      thread_ = Thread::getCurrentThread();
    return data_.transfer();
  }

  void insert(Data* data) {
    Lock l(lock_);
    if (!data_)
      data_.reset(new Set);
    data_->insert(data);
    notify();
  }

  int insert(Set* s) {
    ptr<Set> del(s);
    if (!s)
      return 0;
    int size = s->size();
    if (size) {
      Lock l(lock_);
      if (data_) {
        data_->insert(s->begin(), s->end());
      } else {
        data_.reset(new Set);
        s->swap(*data_);
      }
    }
    return size;
  }

  bool hasUpdates() const {
    Lock l(lock_);
    return thread_ && data_ && !data_->empty();
  }

 private:
  void notify() {
    if (thread_)
      thread_->notify();
  }

  ptr<Set> data_;
  Thread* thread_;
  CriticalSection lock_;

};

DataUpdater::DataUpdater()
  : map_(NULL), update_(new DataSet), write_(new DataSet) {
}

DataUpdater::~DataUpdater() {}

// A piece of data got new information!
void DataUpdater::reportChange(Data* data) {
  update_->insert(data);
}

bool DataUpdater::update() {
  ptr<DataSet::Set> updates(update_->transfer());
  if (!updates)
    return false;
  for (DataSet::Set::iterator i = updates->begin(); i != updates->end(); ++i)
    (*i)->update();

  write_->insert(updates.transfer());
  return true;
}

bool DataUpdater::hasUpdates() const {
  return update_->hasUpdates();
}

bool DataUpdater::write() {
  ptr<DataSet::Set> toWrite(write_->transfer());
  if (toWrite) {
    for (DataSet::Set::iterator i = toWrite->begin(); i != toWrite->end(); ++i)
      (*i)->writeToFile();
  }

  return toWrite && !toWrite->empty();
}

}  // namespace data
}  // namespace rec
