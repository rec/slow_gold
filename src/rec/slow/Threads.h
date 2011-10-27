#ifndef __REC_SLOW_THREADS__
#define __REC_SLOW_THREADS__

#include "rec/slow/HasInstance.h"
#include "rec/util/thread/Looper.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace slow {

struct BufferFiller;

typedef void (*InstanceFunction)(Instance*);
typedef thread::Result (*InstanceLoop)(Instance*);

class Threads : public HasInstance {
 public:
  static const int LOOP_TIME = 100;

  explicit Threads(Instance* i);
  ~Threads();
  void startAll();
  void stop();
  CriticalSection* lock() { return &lock_; }

  void clean();

  Thread* fillThread() { return fillThread_; }
  Thread* bufferThread() { return bufferThread_; }

  template <typename Operator>
  Thread* start(Operator op, const String& name, int priority = 0) {
    Thread* thread = thread::makeLooper(name, op, instance_);
    if (priority)
      thread->setPriority(priority);
    thread->startThread();
    threads_.push_back(thread);
    return thread;
  }

 private:
  typedef std::vector<Thread*> ThreadList;

  ThreadList threads_;
  Thread* fillThread_;
  Thread* bufferThread_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
