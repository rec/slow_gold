#ifndef __REC_PERSIST_ACCESSOR__
#define __REC_PERSIST_ACCESSOR__

#include "rec/base/base.h"
#include "rec/persist/Data.h"
#include "juce_amalgamated.h"

namespace rec {
namespace persist {

template <typename Proto>

class Accessor {
 public:
  Accessor(Data<Proto>* data) : data_(data), locker_(data->lock_) {}

  const Proto& operator*()  const { return data_->proto_; }
  const Proto* operator->() const { return &data_->proto_; }

  Proto& operator*() {
    data_->changed_ = true;
    return data_->proto_;
  }

  Proto* operator->() {
    data_->changed_ = true;
    return &data_->proto_;
  }

 private:
  Data<Proto>* data_;
  ScopedLock locker_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Accessor);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_ACCESSOR__
