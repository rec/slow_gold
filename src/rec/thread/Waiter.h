#ifndef __REC_THREAD_WAITER__
#define __REC_THREAD_WAITER__

#include "rec/thread/Runnable.h"

namespace rec {
namespace thread {

class Waiter : public Runnable {
 public:
  Waiter(int time) : time_(time) {}
  virtual void run(Thread* thread) {
    if (!thread->threadShouldExit())
      thread->wait(time_);
  }

 private:
  const int time_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Waiter);
};

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_WAITER__
