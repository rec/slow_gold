#include "rec/util/BroadcastThread.h"

#include "rec/util/STL.h"

namespace rec {
namespace util {

static const int THREAD_SLEEP = 50;

BroadcastThread::~BroadcastThread() {
  DCHECK_EQ(callables_.size(), 0);
  stl::deletePointers(&callables_);
}

void BroadcastThread::run() {
  while (!threadShouldExit()) {
    uint size;
    {
      Lock l(lock_);
      size = callables_.size();
      if (size) {
        ptr<Callable>(callables_.back())->call();
        callables_.pop_back();
      }
    }
    if (size <= 1)
      wait(THREAD_SLEEP);
  }
}

void BroadcastThread::add(Callable* c) {
  Lock l(lock_);
  callables_.push_front(c);
}

void BroadcastThread::remove(void* owner) {
  Lock l(lock_);
  callables_.remove_if(Callable(owner));
}

// static
BroadcastThread* BroadcastThread::instance() {
  static BroadcastThread bt;
  return &bt;
}

}  // namespace util
}  // namespace rec

