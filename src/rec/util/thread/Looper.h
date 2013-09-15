#ifndef __REC_UTIL_THREAD_LOOPER__
#define __REC_UTIL_THREAD_LOOPER__

#include <unordered_map>

#include "rec/util/thread/Result.h"
#include "rec/util/thread/ThreadList.h"

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
  string name;
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

class LooperThreadList {
 public:
  LooperThreadList() {}
  ~LooperThreadList() { stop(); }

  static const int THREAD_STOP_PERIOD = 2500;

  void add(const LooperDesc& desc) {
    DCHECK(not threads_.count(desc.name));
    threads_[desc.name] = make_unique<ThreadLooper>(desc);
  }

  ThreadLooper* at(const string& name) { return threads_.at(name).get(); }

  void start() {
    for (auto& i: threads_)
      i.second->startThread();
  }

  void stop() {
    for (auto& i: threads_)
    {
      DLOG(INFO) << "stopping thread " << i.first;
      i.second->stopThread(THREAD_STOP_PERIOD);
    }
  }

 private:
  std::unordered_map<string, unique_ptr<ThreadLooper>> threads_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(LooperThreadList);
};

template <typename Iterator>
unique_ptr<LooperThreadList> newLooperList(Iterator begin, Iterator end) {
  unique_ptr<LooperThreadList> threadList(new LooperThreadList);
  for (auto i = begin; i != end; ++i)
    threadList->add(*i);

  return std::move(threadList);
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_LOOPER__
