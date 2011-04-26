#ifndef __REC_UTIL_THREAD_LOCKER__
#define __REC_UTIL_THREAD_LOCKER__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {

template <typename Data>
class Locker {
 public:
  Locker(CriticalSection* lock) : lock_(lock), changed_(false) {}
  virtual ~Locker() {}

  virtual void initialize(const Data& data) {
    ScopedLock l(*lock_);
    data_ = data;
    changed_ = false;
  }

  virtual void change() {
    ScopedLock l(*lock_);
    changed_ = true;
    onChange();
  }

  virtual void set(const Data& data) {
    ScopedLock l(*lock_);
    data_ = data;
    change();
  }

  const Data get() const {
    ScopedLock l(*lock_);
    return data_;
  }

  bool isChanged() const {
    ScopedLock l(*lock_);
    return changed_;
  }

  bool readAndClearChanged(Data* data) {
    ScopedLock l(*lock_);
    *data = data_;
    bool c = changed_;
    changed_ = false;
    return c;
  }

 protected:
  virtual void onChange() {}

 private:
  CriticalSection* lock_;

  Data data_;
  bool changed_;
  DISALLOW_COPY_AND_ASSIGN(Locker);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_LOCKER__
