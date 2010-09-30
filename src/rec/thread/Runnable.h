#ifndef __REC_THREAD_RUNNABLE
#define __REC_THREAD_RUNNABLE

#include "rec/base/base.h"

namespace juce {
class Thread;
}

namespace rec {
namespace thread {

class Runnable {
 public:
  virtual ~Runnable() {}
  virtual void run(Thread* thread) = 0;
  void operator()(Thread* thread) { run(thread); }
};

}  // namespace runnable
}  // namespace rec

#endif  // __REC_THREAD_RUNNABLEX
