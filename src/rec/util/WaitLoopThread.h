#ifndef __REC_WAIT_LOOP_THREAD
#define __REC_WAIT_LOOP_THREAD

#include "juce_amalgamated.h"

namespace rec {
namespace util {

template <typename Callback>
class WaitLoopThread : public Thread {
 public:
  static const int DEFAULT_WAIT = -1;
  WaitLoopThread(const String& s, Callback callback,
                 int waitTime = DEFAULT_WAIT)
      : Thread(s), callback_(callback), waitTime_(waitTime) {
  }

  virtual void run() {
    while (!threadShouldExit()) {
      (*callback_)();
      wait(waitTime_);
    }
  }

  static Thread* New(const String& s, Callback callback,
                     int waitTime = DEFAULT_WAIT) {
    return new WaitLoopThread<Callback>(s, callback, waitTime);
  }

 protected:
  Callback callback_;
  int waitTime_;
};

}  // namespace util
}  // namespace rec

#endif  // __REC_WAIT_LOOP_THREAD
