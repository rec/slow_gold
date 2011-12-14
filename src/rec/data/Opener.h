#ifndef __REC_DATA_OPENER__
#define __REC_DATA_OPENER__

#include "rec/Data/NewData.h"

namespace rec {
namespace data {

template <typename Proto>
struct Opener {
  Opener(Data* d) : data_(d),
                    locker_(new Lock(d->broadcasterLock_)),
                    proto_(dynamic_cast<Proto*>(message_.get())),
                    changed_(false) {
  }

  ~Opener() {
    if (changed_) {
      locker_.reset();  // Close the lock early...
      data_->updateClients();
    }
  }

  const Proto& operator*() const { return *get(); }
  Proto& operator*() { return *get(); }

  const Proto* operator->() const { return get(); }
  Proto* operator->() { return get(); }

  Proto* get() {
    changed_ = true;
    return proto_;
  }

  const Proto* get() const {
    return proto_;
  }

 private_:
  Proto* const proto_;
  Data* const data_;

  ptr<Lock> locker_;
  bool changed_;
};

template <typename Proto>
bool applyToData(bool (*function)(Proto*), Data* data) {
  return function(Opener<Proto>(data).get());
}

template <typename Proto, typename Functor>
bool applyToData(Functor functor, Data* data) {
  return functor(Opener<Proto>(data).get());
}


}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_OPENER__
