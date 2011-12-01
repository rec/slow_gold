#ifndef __REC_UTIL_LISTENER_DATALISTENER__
#define __REC_UTIL_LISTENER_DATALISTENER__

#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/TypedEditable.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Listener.h"
#include "rec/util/UpdateRequester.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace util {
namespace listener {

class UntypedDataListener : public Listener<const Message&>,
                            public Listener<const VirtualFile&>,
                            public UpdateRequester {
 public:
  UntypedDataListener(const string& typeName,
                      const data::Address& address =
                      data::Address::default_instance(),
                      bool isGlobal = false);

  virtual void requestUpdates();

  virtual void operator()(const Message&);
  virtual void operator()(const VirtualFile&);

 protected:
  virtual void setData(data::UntypedEditable* d);
  virtual void onDataChange();

 private:
  const data::Address address_;
  const bool isGlobal_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedDataListener);
};

template <typename Proto>
class DataListener : public Listener<const Proto&>,
                     public Listener<const VirtualFile&>,
                     public UpdateRequester {
 public:
  DataListener(const data::Address& address =
               data::Address::default_instance(),
               bool isGlobal = false);
  virtual ~DataListener() {}

  virtual void requestUpdates();

  virtual void operator()(const Proto&);
  virtual void operator()(const VirtualFile&);

  data::TypedEditable<Proto>* data() const { Lock l(lock()); return data_; }

  virtual const data::Value getValue() const { return data()->getValue(address_); }
  virtual void setValue(const data::Value& v) { data()->setValue(v, address_); }
  void setProto(const Proto& p) { data()->setValue(p, address_); }

 protected:
  virtual void setData(data::TypedEditable<Proto>* d);
  virtual void onDataChange(const Proto&) {}
  const data::Address& address() const { return address_; }
  const CriticalSection& lock() const { return Listener<const Proto&>::lock(); }

 private:
  data::TypedEditable<Proto>* data_;
  const data::Address address_;
  const bool isGlobal_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataListener);
};


template <typename Proto>
class GlobalDataListener : public DataListener<Proto> {
 public:
  GlobalDataListener(const data::Address& address =
               data::Address::default_instance())
      : DataListener<Proto>(address, true) {
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(GlobalDataListener);
};


//
// Implementations
//

template <typename Proto>
DataListener<Proto>::DataListener(const data::Address& address,
                                  bool isGlobal)
    : data_(data::emptyEditable<Proto>()),
      address_(address),
      isGlobal_(isGlobal) {
}

template <typename Proto>
void DataListener<Proto>::requestUpdates() {
  if (isGlobal_)
    setData(data::editable<Proto>());
  else
    data::editable<VirtualFile>()->addListener(this);
}

template <typename Proto>
void DataListener<Proto>::operator()(const VirtualFile& f) {
  setData(file::empty(f) ? data::emptyEditable<Proto>() :
          data::editable<Proto>(f));
}


template <typename Proto>
void DataListener<Proto>::operator()(const Proto& p) {
  onDataChange(p);
}

template <typename Proto>
void DataListener<Proto>::setData(data::TypedEditable<Proto>* d) {
  Proto p;
  {
    Lock l(lock());
    data_->removeListener(this);
    data_ = d;
    data_->addListener(this);
  }
}

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
