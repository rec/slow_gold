#ifndef __REC_THREAD_LOOP__
#define __REC_THREAD_LOOP__

#include "rec/thread/Wrapper.h"

namespace rec {
namespace thread {

class Loop : public Wrapper {
 public:
  Loop(Runnable* r) : Wrapper(r) {}

  virtual void run(Thread* thread) {
    while (!thread->threadShouldExit())
      runnable_->run();
  }

 protected:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Loop);
};

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_LOOP__
