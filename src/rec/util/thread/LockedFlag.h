#ifndef __REC_UTIL_THREAD_LOCKEDFLAG__
#define __REC_UTIL_THREAD_LOCKEDFLAG__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {

template <typename Type>
class LockedFlag {
 public:
  explicit LockedFlag(Type flag) : flag_(flag) {}

  // Atomically sets the flag
  bool setFlag(Type f) {
    Lock l(lock_);
    if (flag_)
      return false;
    flag_ = f;
    return true;
  }

  bool tryToTakeSpin(Type flag, int intervalMs = 10, int intervalCount = 100) {
    Thread* t = getCurrentThread();
    for (int i = 0; i < intervalCount && !(t && t->threadShouldExit()); ++i) {
      if (setFlag(flag))
        return true;
      Thread::sleep(intervalMs);
    }
    return false;
  }

  void resetFlag() {
    Lock l(lock_);
    flag_ = Type(0);
  }

 private:
  CriticalSection lock_;
  Type flag_;

  DISALLOW_COPY_AND_ASSIGN(LockedFlag);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_LOCKEDFLAG__
