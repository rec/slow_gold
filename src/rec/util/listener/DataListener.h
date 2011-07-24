#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/util/listener/Listener.h"
#include "rec/data/persist/Data.h"
#include "rec/data/proto/Proto.h"
#include "rec/data/persist/App.h"
#include "rec/data/persist/Persist.h"

namespace rec {
namespace util {
namespace listener {

// DataListener listens to changes in persistent data.

template <typename Proto>
class DataListener : public Listener<const Proto&>,
                     public Listener<const VirtualFile&> {
 public:
  DataListener();

  virtual ~DataListener() { setData(NULL); }
  virtual void operator()(const VirtualFile& f) { setFile(f); }
  virtual void setFile(const VirtualFile& file);

  virtual void operator()(const Proto& p);

  const Proto get() const;

 protected:
  virtual void setData(persist::Data<Proto>* d);

 protected:
  virtual void onDataChange(const Proto&) = 0;

  CriticalSection lock_;
  persist::Data<Proto>* data_;
  Proto proto_;

 private:
  DISALLOW_COPY_AND_ASSIGN(DataListener);
};

template <typename Proto>
DataListener<Proto>::DataListener() : data_(NULL) {
  persist::setter<VirtualFile>()->addListener(this);
}

template <typename Proto>
void DataListener<Proto>::setFile(const VirtualFile& file) {
  LOG(INFO) << "setFile " << Proto::default_instance().GetTypeName();
  setData(persist::setter<Proto>(file));
}

template <typename Proto>
void DataListener<Proto>::operator()(const Proto& p) {
  {
    ScopedLock l(lock_);
    proto_ = p;
  }
  onDataChange(p);
}

template <typename Proto>
const Proto DataListener<Proto>::get() const {
  ScopedLock l(lock_);
  return proto_;
}

template <typename Proto>
void DataListener<Proto>::setData(persist::Data<Proto>* d) {
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
