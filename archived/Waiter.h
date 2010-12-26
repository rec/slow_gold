#ifndef __REC_THREAD_WAITER__
#define __REC_THREAD_WAITER__

#include "rec/util/thread/Runnable.h"

namespace rec {
namespace util {
namespace thread {

class Waiter : public Runnable {
 public:
  Waiter(int time) : time_(time) {}
  virtual bool run(Thread* thread) {
    if (thread->threadShouldExit())
      return false;

    thread->wait(time_);
    return true;
  }

 private:
  const int time_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Waiter);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_WAITER__
