#ifndef __REC_THREAD_WRAPPER
#define __REC_THREAD_WRAPPER

#include "rec/util/thread/Runnable.h"

namespace rec {
namespace util {
namespace thread {

class Wrapper : public Runnable {
 public:
  Wrapper(Runnable* r) : runnable_(r) {}
  virtual bool run(Thread* thread) { return runnable_->run(thread); }

 protected:
  ptr<Runnable> runnable_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrapper);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_WRAPPER
