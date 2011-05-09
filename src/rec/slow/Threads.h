#ifndef __REC_SLOW_THREADS__
#define __REC_SLOW_THREADS__

#include "rec/slow/HasInstance.h"
#include "rec/util/thread/Trash.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace slow {

struct Model;

typedef void (*InstanceFunction)(Instance*);

class Threads : public HasInstance {
 public:
  static const int LOOP_TIME = 100;

  explicit Threads(Instance* i);
  ~Threads();
  void startAll();
  void stop();
  CriticalSection* lock() { return &lock_; }

  void clean();

  // waitTime >= means run and wait in a loop.
  // waitTime 0 means run once.
  // waitTime < 0 means run and wait forever (till a notify).
  Thread* start(InstanceFunction f, const String& name, int waitTime = 0);
  Thread* start(Callback* cb, const String& name, int waitTime = 0);
  Thread* fetchThread() { return fetchThread_; }
  Thread* bufferThread() { return bufferThread_; }

 private:
  typedef std::vector<Thread*> ThreadList;

  ThreadList threads_;
  Thread* fetchThread_;
  Thread* bufferThread_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
