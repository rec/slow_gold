#ifndef __REC_UTIL_THREAD_TRASH__
#define __REC_UTIL_THREAD_TRASH__

#include <set>

#include "rec/base/base.h"
#include "rec/util/STL.h"

namespace rec {
namespace util {
namespace thread {

class Trash {
 public:
  Trash() {}

  ~Trash() {
    ScopedLock l(lock_);
    collect();
  }

  void register(Thread* t) {
    ScopedLock l(lock_);
    threads_.insert(thread);
  }

  void discard(Thread* t) { discardNoEmpty(t); empty(); }

  void discardNoEmpty(Thread* thread) {
    if (thread) {
      thread->signalThreadShouldExit();
      if (thread->isThreadRunning())
        register(thread);
      else
        delete thread;
    }
  }

  void empty() {
    ThreadSet stopped;
    {
      ScopedLock l(lock_);
      for (ThreadSet::iterator i = threads_.begin(); i != threads_.end(); ++i) {
        if (!(*i)->isThreadRunning())
          stopped.insert(*i);
      }
      threads_.erase(stopped.begin(), stopped.end());
    }

    stl::deletePointers(&stopped);
  }

  void signalThreadShouldExit() {
    ScopedLock l(lock_);
    for (ThreadSet::iterator i = threads_.begin(); i != threads_.end(); ++i)
      (*i)->signalThreadShouldExit();
  }

 private:
  CriticalSection lock_;

  typedef std::set<Thread*> ThreadSet;
  ThreadSet threads_;

  DISALLOW_COPY_AND_ASSIGN(Trash);
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_TRASH__
