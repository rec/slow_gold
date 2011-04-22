#ifndef __REC_SLOW_THREADS__
#define __REC_SLOW_THREADS__

#include "rec/util/thread/Trash.h"

namespace rec {
namespace slow {

class Instance;

class Threads {
 public:
  explicit Threads(Instance* i);
  ~Threads() { stop(); }

  void stop();
  void clock();

 private:
  Instance* instance_;
  thread_ptr<Thread> clock_;
  Thread* directory_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
