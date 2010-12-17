#ifndef __REC_THREAD_LOOP__
#define __REC_THREAD_LOOP__

#include "rec/util/thread/Wrapper.h"

namespace rec {
namespace util {
namespace thread {

class Loop : public Wrapper {
 public:
  Loop(Runnable* r) : Wrapper(r) {}

  virtual bool run(Thread* thread) {
    while (!(thread->threadShouldExit() && runnable_->run(thread)));
    return false;
  }

 protected:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Loop);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_LOOP__
