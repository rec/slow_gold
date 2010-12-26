#ifndef __REC_THREAD_LOOP__
#define __REC_THREAD_LOOP__

#include "rec/util/thread/Wrapper.h"

namespace rec {
namespace util {
namespace thread {

class Loop : public CallbackWrapper {
 public:
  Loop(CallbackMessage* msg) : CallbackWrapper(msg) {}

  virtual void messageCallback() {
    Thread* thread = Thread::getCurrentThread();
    while (!(thread && threadShouldExit()))
      get()->messageCallback();
  }

 protected:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Loop);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_LOOP__
