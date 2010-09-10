#ifndef __REC_THREAD_RUNNABLE
#define __REC_THREAD_RUNNABLE

#include "rec/base/basictypes.h"
#include "JuceLibraryCode/JuceHeader.h"

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
