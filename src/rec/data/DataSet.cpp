#include "rec/data/DataSet.h"

namespace rec {
namespace data {

DataSet::Set* DataSet::release() {
  Lock l(lock_);
  if (!thread_)
    thread_ = Thread::getCurrentThread();
  return data_.release();
}

void DataSet::insert(Data* data) {
  Lock l(lock_);
  if (!data_)
    data_.reset(new Set);
  DCHECK(data_->insert(data).second);
  notify();
}

int DataSet::insert(Set* s) {
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

bool DataSet::hasUpdates() const {
  Lock l(lock_);
  return thread_ && data_ && !data_->empty();
}

void DataSet::notify() {
  if (thread_)
    thread_->notify();
}

}  // namespace data
}  // namespace rec
