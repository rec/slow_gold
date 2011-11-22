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

template <typename Proto>
class GlobalDataListener : public Listener<const Proto&>,
                           public UpdateRequester {
 public:
  static const bool FILTER = false;

  GlobalDataListener(const data::Address& address = data::Address::default_instance())
      : filterDupes_(false), data_(data::emptyEditable<Proto>()), address_(address) {
  }
  virtual ~GlobalDataListener() {}

  virtual void requestUpdates() {
    setData(data::editable<Proto>());
  }

  virtual void operator()(const Proto& p) { updateValue(p, true); }

  data::TypedEditable<Proto>* data() const { Lock l(this->lock_); return data_; }

  virtual const data::Value getValue() const { return data()->getValue(address_); }
  virtual void setValue(const data::Value& v) { data()->setValue(v, address_); }

 protected:
  virtual void setData(data::TypedEditable<Proto>* d);
  virtual void onDataChange(const Proto&) {}
  const data::Address& address() const { return address_; }
  CriticalSection* lock() const { return &Listener<Proto>::lock_; }

 private:
  void doOnDataChange(const Proto& p) { onDataChange(p); }
  void updateValue(const Proto& p, bool perhapsFilter);

  const bool filterDupes_;
  data::TypedEditable<Proto>* data_;
  Proto proto_;
  const data::Address address_;

  DISALLOW_COPY_AND_ASSIGN(GlobalDataListener);
};

// DataListener listens to changes in persistent data.

template <typename Proto>
class DataListener : public GlobalDataListener<Proto>,
                     public Listener<const VirtualFile&> {
 public:
  DataListener(const data::Address& addr = data::Address::default_instance())
      : GlobalDataListener<Proto>(addr) {
  }
  virtual ~DataListener() {}

  virtual void requestUpdates() {
    data::editable<VirtualFile>()->addListener(this);
  }

  virtual void operator()(const VirtualFile& f) {
    setData(file::empty(f) ? data::emptyEditable<Proto>() :
            data::editable<Proto>(f));
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(DataListener);
};

//
// Implementations
//

template <typename Proto>
void GlobalDataListener<Proto>::updateValue(const Proto& p, bool perhapsFilter) {
  {
    Lock l(this->lock_);
    if (perhapsFilter && filterDupes_ && data::equals(proto_, p))
      return;
    proto_ = p;
  }

  onDataChange(p);
}

template <typename Proto>
void GlobalDataListener<Proto>::setData(data::TypedEditable<Proto>* d) {
  Proto p;
  {
    Lock l(this->lock_);
    data_->removeListener(this);
    data_ = d;
    data_->addListener(this);
  }
}

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_DATALISTENER__
