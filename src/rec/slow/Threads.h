#ifndef __REC_SLOW_THREADS__
#define __REC_SLOW_THREADS__

#include "rec/util/thread/Looper.h"

namespace rec {
namespace slow {

class Threads {
 public:
  Threads();
  ~Threads();

  void start();
  void clean();
  void stop();

  Thread* timerThread();

 private:
  unique_ptr<util::thread::LooperThreadList> threads_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
