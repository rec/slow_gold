#ifndef __REC_THREAD_LOCKEDMESSAGE__
#define __REC_THREAD_LOCKEDMESSAGE__

#include "rec/util/thread/Wrapper.h"

namespace rec {
namespace thread {

class LockedMessage : public Wrapper {
 public:
  LockedMessage(Runnable* r) : Wrapper(r) {}

  virtual void run(Thread* thread) {
    MessageManagerLock lock(thread);
    if (lock.lockWasGained())
      runnable_->run(thread);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(LockedMessage);
};

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_LOCKEDMESSAGE__
