#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/TypedEditable.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/Data.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace util {
namespace listener {

template <typename Proto>
class DataListenerBase : public Listener<const Proto&> {
 public:
  DataListenerBase(bool fd = false) : filterDupes_(fd) {}
  virtual ~DataListenerBase() {}

  virtual void operator()(const Proto& p);
  virtual const Proto get() const { Lock l(lock_); return proto_; }

  static const bool UPDATE_ON_MESSAGE_THREAD = !true;  // TODO: fix!

 protected:
  data::TypedEditable<Proto>* data() { return data_; }
  virtual void setData(data::TypedEditable<Proto>* d);
  virtual void onDataChange(const Proto&) = 0;

 private:
  void doOnDataChange(const Proto& p) { onDataChange(p); }

  CriticalSection lock_;
  data::TypedEditable<Proto>* data_;
  Proto proto_;

  const bool filterDupes_;

  DISALLOW_COPY_AND_ASSIGN(DataListenerBase);
};

template <typename Proto>
void DataListenerBase<Proto>::operator()(const Proto& p) {
  {
    Lock l(lock_);
    if (filterDupes_ && data::equals(proto_, p))
      return;
    proto_ = p;
  }
  if (UPDATE_ON_MESSAGE_THREAD)
    thread::callAsync(this, &DataListenerBase<Proto>::doOnDataChange, p);
  else
    onDataChange(p);
}

template <typename Proto>
void DataListenerBase<Proto>::setData(data::TypedEditable<Proto>* d) {
  if (data_ != d) {
    if (data_)
      data_->removeListener(this);

    data_ = d;

    if (data_) {
      data_->addListener(this);
      (*this)(data_->get());
    }
  }
}


// DataListener listens to changes in persistent data.

template <typename Proto>
class DataListener : public DataListenerBase<Proto>,
                     public Listener<const VirtualFile&> {
 public:
  DataListener(bool filterDupes = false) : DataListenerBase<Proto>(filterDupes) {
    data::editable<VirtualFile>()->addListener(this);
  }

  virtual ~DataListener() {}

  virtual void operator()(const VirtualFile& f) {
    this->setData(data::editable<Proto>(f));
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(DataListener);
};


}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
