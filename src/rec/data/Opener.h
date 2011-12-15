#ifndef __REC_DATA_OPENER__
#define __REC_DATA_OPENER__

#include "rec/Data/NewData.h"

namespace rec {
namespace data {

template <typename Proto>
struct Opener {
  Opener(Data* d, bool undoable = true)
      : data_(d),
        locker_(new Lock(d->lock_)),
        proto_(dynamic_cast<Proto*>(d->message_.get())),
        changed_(false),
        undoable_(undoable),
        before_(*proto_) {
  }

  ~Opener() {
    if (changed_)
      data_->reportChange(before_, undoable_);
   }

  const Proto& operator*() const { return get(); }
  Proto& operator*() { return *mutable_get(); }

  const Proto* operator->() const { return &get(); }
  Proto* operator->() { return mutable_get(); }

  Proto* mutable_get() {
    changed_ = true;
    return proto_;
  }

  const Proto& get() const {
    return *proto_;
  }

 private_:
  Data* const data_;
  ptr<Lock> locker_;
  Proto* const proto_;
  bool changed_;
  bool undoable_;
  Message before_;
};

template <typename Proto>
struct Opener : public UntypedOpener {
  Opener(Data* d, bool undoable = true)
      : UntypedOpener(d, undoable),

template <typename Proto>
bool applyToData(bool (*function)(Proto*), Data* data) {
  return function(Opener<Proto>(data).mutable_get());
}

template <typename Proto, typename Functor>
bool applyToData(Functor functor, Data* data) {
  return functor(Opener<Proto>(data).mutable_get());
}

inline void updateClients(Data* data) {
  data->broadcast(ptr<Message>(Opener<Message>(data).get()));
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_OPENER__
