#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/Data.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace util {
namespace listener {

// DataListener listens to changes in persistent data.

template <typename Proto>
class DataListener : public Listener<const Proto&>,
                     public Listener<const VirtualFile&> {
 public:
  DataListener(bool filterDupes = false);
  virtual ~DataListener() { } // setData(NULL); }

  virtual void operator()(const VirtualFile& f) { setFile(f); }
  virtual void operator()(const Proto& p);
  virtual const Proto get() const;
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

  virtual void setFile(const VirtualFile& file);

  const bool filterDupes_;

  DISALLOW_COPY_AND_ASSIGN(DataListener);
};

//
// Implementations.
//

template <typename Proto>
DataListener<Proto>::DataListener(bool f) : data_(NULL), filterDupes_(f) {
  data::editable<VirtualFile>()->addListener(this);
}

template <typename Proto>
void DataListener<Proto>::setFile(const VirtualFile& file) {
  setData(data::editable<Proto>(file));
}

template <typename Proto>
void DataListener<Proto>::operator()(const Proto& p) {
  {
    ScopedLock l(lock_);
    if (filterDupes_ && data::equals(proto_, p))
      return;
    proto_ = p;
  }
  if (UPDATE_ON_MESSAGE_THREAD)
    thread::callAsync(this, &DataListener<Proto>::doOnDataChange, p);
  else
    onDataChange(p);
}

template <typename Proto>
const Proto DataListener<Proto>::get() const {
  ScopedLock l(lock_);
  return proto_;
}

template <typename Proto>
void DataListener<Proto>::setData(data::TypedEditable<Proto>* d) {
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


}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
