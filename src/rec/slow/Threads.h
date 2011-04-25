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
  void startAll();
  void stop();
  CriticalSection* lock() { return &lock_; }

 private:
  typedef std::vector<Thread*> ThreadList;
  typedef void (*InstanceFunction)(Instance*);

  void start(InstanceFunction f, const String& name, int waitTime = LOOP_TIME);

  Instance* instance_;
  ThreadList threads_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
