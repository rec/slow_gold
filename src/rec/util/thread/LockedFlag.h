#ifndef __REC_UTIL_THREAD_LOCKEDFLAG__
#define __REC_UTIL_THREAD_LOCKEDFLAG__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {

template <typename Type = bool>
class LockedFlag {
 public:
  explicit LockedFlag(int intervalMs = 5, int intervalCount = 1000)
      : flag_(0), intervalMs_(intervalMs), intervalCount_(intervalCount) {
  }

  bool tryToTakeSpin(Type t) {
    Thread* thread = getCurrentThread();
    for (int i = 0; intervalCount_ <= 0 || i < intervalCount; ++i) {
      if (thread && thread->threadShouldExit())
        return false;
      if (set(t))
        return true;
      Thread::sleep(intervalMs);
    }
    return false;
  }

  // You can only call reset if "tryToTakeSpin" returned true.
  void reset() {
    Lock l(lock_);

  }

 private:
  // Atomically sets the flag
  bool set(Type f) {
    Lock l(lock_);
    if (flag_)
      return false;
    flag_ = f;
    return true;
  }

  CriticalSection lock_;
  Type flag_;
  const int intervalMs_;
  const int intervalCount_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(LockedFlag);
};

template <typename Type = bool>
class FlagLocker {
 public:
  FlagLocker(LockedFlag* flag, Type t) : flag_(flag),
                                         failed_(flag_->tryToTakeSpin(t)) {
  }

  ~FlagLocker() {
    if (!failed_)
      flag_->reset();
  }

  bool failed() const { return failed_; }

 private:
    LockedFlag* const flag_;
  const bool failed_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(LockedFlag);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_LOCKEDFLAG__
