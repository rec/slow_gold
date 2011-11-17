#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/util/listener/Listener.h"
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
  DataListenerBase(const data::Address& address = data::Address::default_instance())
      : filterDupes_(true), data_(NULL), address_(address) {
  }
  virtual ~DataListenerBase() {}

  virtual void operator()(const Proto& p);

  virtual const Proto get() const {
    return data() ? data()->get() : Proto::default_instance();
  }
  virtual const data::Value getValue() const {
    return data() ? data()->getValue(address_) : data::Value::default_instance();
  }

  virtual void setValue(const data::Value& value) {
    if (data())
      data()->setValue(value, address_);
  }

  virtual void set(const Proto& proto) {
    if (data())
      data()->setValue(proto);
  }

  static const bool UPDATE_ON_MESSAGE_THREAD = !true;  // TODO: fix!

 protected:
  data::TypedEditable<Proto>* data() const { return data_; }
  virtual void setData(data::TypedEditable<Proto>* d);  // TODO: change to setEditable.
  virtual void onDataChange(const Proto&) {}
  const data::Address& address() const { return address_; }

 private:
  void doOnDataChange(const Proto& p) { onDataChange(p); }

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
  DataListener(const data::Address& address = data::Address::default_instance())
      : DataListenerBase<Proto>(address) {
    data::editable<VirtualFile>()->addListener(this);
  }

  virtual ~DataListener() {}

  virtual void operator()(const VirtualFile& f) {
    setData(data::editable<Proto>(f));
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

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
