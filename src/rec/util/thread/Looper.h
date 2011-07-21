#ifndef __REC_UTIL_THREAD_LOOPER__
#define __REC_UTIL_THREAD_LOOPER__

#include "rec/util/thread/Result.h"

namespace rec {
namespace util {
namespace thread {

template <typename Operator, typename Instance>
class Looper : public Thread {
 public:
  Looper(const String& name, Operator op, Instance i) : Thread(name), op_(op), instance_(i) {}

  virtual void run() {
    while (!threadShouldExit()) {
      // DLOG(INFO) << str(getThreadName());
      Result r = static_cast<Result>(op_(instance_));
      switch (r) {
       case CONTINUE:  break;
       case YIELD:     yield(); break;
       case DONE:      return;
       default:        wait(static_cast<int>(r)); break;
      }
    }
  }

 private:
  Operator const op_;
  Instance const instance_;

  DISALLOW_COPY_AND_ASSIGN(Looper);
};

template <typename Operator, typename Instance>
Thread* makeLooper(String name, Operator op, Instance i) {
  return new Looper<Operator, Instance>(name, op, i);
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_LOOPER__
