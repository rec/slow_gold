#ifndef __REC_THREAD_RUNNABLETHREAD
#define __REC_THREAD_RUNNABLETHREAD

#include "rec/util/thread/Runnable.h"
#include "rec/util/thread/Wrapper.h"

namespace rec {
namespace thread {

class RunnableThread : public Thread, public Wrapper {
 public:
  RunnableThread(const String& n, Runnable* r) : Thread(n), Wrapper(r) {}

  virtual void run() { runnable_->run(this); }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(RunnableThread);
};

}  // namespace runnable
}  // namespace rec

#endif  // __REC_THREAD_RUNNABLETHREADX
