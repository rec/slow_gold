#ifndef __REC_THREAD_WRAPPER
#define __REC_THREAD_WRAPPER

#include "rec/util/thread/Runnable.h"

namespace rec {
namespace thread {

class Wrapper : public Runnable {
 public:
  Wrapper(Runnable* r) : runnable_(r) {}
  virtual void run(Thread* thread) { runnable_->run(thread); }

 protected:
  scoped_ptr<Runnable> runnable_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrapper);
};

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_WRAPPER
