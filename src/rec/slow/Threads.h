#ifndef __REC_SLOW_THREADS__
#define __REC_SLOW_THREADS__

#include "rec/util/thread/Trash.h"

namespace rec {
namespace slow {

class Instance;

class Threads {
 public:
  static const int LOOP_TIME = 100;

  explicit Threads(Instance* i);
  ~Threads();
  void stop();

  typedef void (*InstanceFunction)(Instance*);
  void start(InstanceFunction f, const String& name, int waitTime = LOOP_TIME);

 private:
  typedef std::vector<Thread*> ThreadList;

  Instance* instance_;
  ThreadList threads_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
