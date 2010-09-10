#ifndef __REC_THREAD_WAITLOOP__
#define __REC_THREAD_WAITLOOP__

#include "rec/thread/Cycler.h"
#include "rec/thread/Waiter.h"
#include "rec/thread/Loop.h"

namespace rec {
namespace thread {

class WaitLoop : public Loop {
 public:
  WaitLoop(int time, Runnable* r) : Loop(new Cycler(r, new Waiter(time))) {}

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(WaitLoop);
};

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_WAITLOOP__
