#ifndef __REC_THREAD_RUNNABLETHREAD
#define __REC_THREAD_RUNNABLETHREAD

#include "rec/util/thread/Runnable.h"
#include "rec/util/thread/Wrapper.h"

namespace rec {
namespace util {
namespace thread {

class RunnableThread : public Thread, public Wrapper {
 public:
  static const int SHUTDOWN_DELAY = 1000;
  RunnableThread(const String& n, Runnable* r) : Thread(n), Wrapper(r) {}
  ~RunnableThread() { stopThread(SHUTDOWN_DELAY); }

  virtual void run() { (*this)(); }
  bool operator()() {
    return runnable_->run(this);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(RunnableThread);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_RUNNABLETHREADX
