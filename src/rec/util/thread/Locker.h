#ifndef __REC_UTIL_THREAD_LOCKER__
#define __REC_UTIL_THREAD_LOCKER__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {

template <typename Data>
class Locker {
 public:
  Locker() : changed_(false) {}
  virtual ~Locker() {}

  virtual void onChange() {}

  virtual void change() {
    ScopedLock l(lock_);
    changed_ = true;
    onChange();
  }

  virtual void set(const Data& data) {
    ScopedLock l(lock_);
    data_ = data;
    change();
  }

  const Data get() const {
    ScopedLock l(lock_);
    return data_;
  }

  bool isChanged() const {
    ScopedLock l(lock_);
    return changed_;
  }

  bool getDataIfChanged(Data* data) {
    ScopedLock l(lock_);
    if (!changed_)
      return false;

    changed_ = false;
    *data = data_;
    return true;
  }

  CriticalSection& lock() { return lock_; }

 private:
  CriticalSection lock_;

  Data data_;
  bool changed_;
  DISALLOW_COPY_AND_ASSIGN(Locker);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_LOCKER__
