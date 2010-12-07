#include <glog/logging.h>

#include "rec/util/thread/Trash.h"

namespace rec {
namespace util {
namespace thread {
namespace trash {

namespace {

class Trash {
 public:
  Trash() {}

  ~Trash() {
    ScopedLock l(lock_);
    empty();
  }

  void doDelete(Thread* thread) {
    DLOG(INFO) << "Deleting thread " << thread->getThreadName();
    delete thread;
  }

  void discard(Thread* thread) {
    if (thread) {
      thread->signalThreadShouldExit();
      thread->notify();
      if (thread->isThreadRunning()) {
        ScopedLock l(lock_);
        threads_.insert(thread);
      } else {
        doDelete(thread);
      }
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

    for (ThreadSet::iterator i = stopped.begin(); i != stopped.end(); ++i)
      doDelete(*i);
  }

  void waitForAllThreadsToExit(int timeout) {
    ScopedLock l(lock_);
    for (ThreadSet::iterator i = threads_.begin(); i != threads_.end(); ++i)
      (*i)->waitForThreadToExit(timeout);
  }

 private:
  CriticalSection lock_;

  typedef std::set<Thread*> ThreadSet;
  ThreadSet threads_;

  DISALLOW_COPY_AND_ASSIGN(Trash);
};

Trash* instance() {
  static Trash trash;
  return &trash;
}

}  // namespace

void discard(Thread* t) { instance()->discard(t); }
void empty() { instance()->empty(); }
void waitForAllThreadsToExit(int t) { instance()->waitForAllThreadsToExit(t); }


}  // namespace trash
}  // namespace thread
}  // namespace util
}  // namespace rec
