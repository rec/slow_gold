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
      Result r = execute();
      switch (r) {
       case CONTINUE:  break;
       case YIELD:     yield(); break;
       case DONE:      return;
       default:        wait(static_cast<int>(r)); break;
      }
    }
  }

  virtual Result execute() const{
    return static_cast<Result>(op_(instance_));
  }

 private:
  Operator const op_;
  Instance const instance_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Looper);
};

template <typename Operator, typename Instance>
unique_ptr<Thread> makeLooper(String name, Operator op, Instance i) {
  return make_unique<Looper<Operator, Instance>>(name, op, i);
}

typedef int32 (*ThreadFunction)(Thread*);

struct LooperDesc {
  String name;
  int32 priority;
  int32 period;
  ThreadFunction function;
};

class ThreadLooper : public Thread {
 public:
  explicit ThreadLooper(const LooperDesc&);
  void run() override;

 private:
  ThreadFunction const function_;
  int32 const period_;
};

inline unique_ptr<Thread> newThread(const LooperDesc& ld) {
  return unique_ptr<Thread>(new ThreadLooper(ld));
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_LOOPER__
