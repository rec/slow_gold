#ifndef __REC_LOCKER
#define __REC_LOCKER

#include "rec/base/scoped_ptr.h"

// Generic holder of locks during a scope.

namespace rec {
namespace util {

class LockInterface {
 public:
  virtual ~LockInterface() {}
  virtual void enter() = 0;
  virtual void exit() = 0;
};

class Locker {
 public:
  Locker(scoped_ptr<LockInterface>* lock) : lock_(lock->get()) {
    lock_->enter();
  }

  Locker(LockInterface* lock) : lock_(lock) {
    lock_->enter();
  }

  ~Locker() {
    lock_->exit();
  }

 private:
  LockInterface* lock_;
};

#if 0
class CriticalSectionLock : public LockInterface {
 private:
  CriticalSection lock_;

 public:

  void enter() { lock_->enter(); }
  void exit() { lock_->exit(); }
};

#endif

}  // namespace util
}  // namespace rec


#endif  // __REC_LOCKER
