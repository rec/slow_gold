#ifndef __REC_THREAD_RUNNABLE
#define __REC_THREAD_RUNNABLE

#include "rec/base/base.h"


namespace rec {
namespace util {
namespace thread {

class Runnable {
 public:
  virtual ~Runnable() {}
  virtual bool run(Thread* thread) = 0;
  bool operator()(Thread* thread) { return run(thread); }
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_RUNNABLEX
