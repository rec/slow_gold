#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/util/Listener.h"
#include "rec/data/TypedEditable.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/Value.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace util {
namespace listener {

template <typename Proto>
class DataListenerBase : public Listener<const Proto&> {
 public:
  static const bool FILTER = false;

  DataListenerBase(const data::Address& address = data::Address::default_instance())
      : filterDupes_(false), data_(data::emptyEditable<Proto>()), address_(address) {
  }
  virtual ~DataListenerBase() {}

  virtual void operator()(const Proto& p) { updateValue(p, true); }

  data::TypedEditable<Proto>* data() const { Lock l(lock_); return data_; }

  virtual const data::Value getValue() const { return data()->getValue(address_); }
  virtual void setValue(const data::Value& v) { data()->setValue(v, address_); }

 protected:
  virtual void setData(data::TypedEditable<Proto>* d);
  virtual void onDataChange(const Proto&) {}
  const data::Address& address() const { return address_; }

 private:
  void doOnDataChange(const Proto& p) { onDataChange(p); }
  void updateValue(const Proto& p, bool perhapsFilter);

  CriticalSection lock_;
  const bool filterDupes_;
  data::TypedEditable<Proto>* data_;
  Proto proto_;
  const data::Address address_;

  DISALLOW_COPY_AND_ASSIGN(DataListenerBase);
};

// DataListener listens to changes in persistent data.

template <typename Proto>
class DataListener : public DataListenerBase<Proto>,
                     public Listener<const VirtualFile&> {
 public:
  DataListener(const data::Address& addr = data::Address::default_instance())
      : DataListenerBase<Proto>(addr) {
    data::editable<VirtualFile>()->addListener(this);
  }

  virtual ~DataListener() {}

  virtual void operator()(const VirtualFile& f) {
    setData(file::empty(f) ? data::emptyEditable<Proto>() :
            data::editable<Proto>(f));
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(DataListener);
};

template <typename Proto>
class GlobalDataListener : public DataListenerBase<Proto> {
 public:
  GlobalDataListener(const data::Address& address = data::Address::default_instance())
      : DataListenerBase<Proto>(address) {
    setData(data::editable<Proto>());
  }

  virtual ~GlobalDataListener() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(GlobalDataListener);
};

//
// Implementations
//

template <typename Proto>
void DataListenerBase<Proto>::updateValue(const Proto& p, bool perhapsFilter) {
  {
    Lock l(lock_);
    if (perhapsFilter && filterDupes_ && data::equals(proto_, p))
      return;
    proto_ = p;
  }

  onDataChange(p);
}

template <typename Proto>
void DataListenerBase<Proto>::setData(data::TypedEditable<Proto>* d) {
  Proto p;
  {
    Lock l(lock_);
    data_->removeListener(this);
    data_ = d;
    data_->addListener(this);
  }
}

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
