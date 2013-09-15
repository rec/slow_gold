#include "rec/util/thread/Looper.h"

namespace rec {
namespace util {
namespace thread {

ThreadLooper::ThreadLooper(const LooperDesc& desc)
    : Thread(desc.name), function_(desc.function), period_(desc.period) {
  setPriority(desc.priority);
}

void ThreadLooper::run() {
  while (!threadShouldExit()) {
    int32 r = function_(this);
    switch (r) {
     case CONTINUE:
      break;

     case YIELD:
      yield();
      break;

     case DONE:
      return;

     case WAIT:
       wait(period_);
       break;

     default:
      wait(r);
      break;
    }
  }
}

}  // namespace thread
}  // namespace util
}  // namespace rec
