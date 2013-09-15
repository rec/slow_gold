#ifndef __REC_UTIL_THREAD_THREADLIST__
#define __REC_UTIL_THREAD_THREADLIST__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {

class ThreadList {
 public:
  ThreadList() {}
  ~ThreadList() { stop(); }

  static const int THREAD_STOP_PERIOD = 2500;

  void add(unique_ptr<Thread> thread) {
    threads_.push_back(std::move(thread));
  }

  void stop() {
    for (uint i = 0; i < threads_.size(); ++i)
      threads_[i]->stopThread(THREAD_STOP_PERIOD);
  }

 private:
  vector<unique_ptr<Thread>> threads_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(ThreadList);
};

template <typename Maker, typename Iterator>
unique_ptr<ThreadList> newThreadList(Maker maker, Iterator begin, Iterator end) {
  unique_ptr<ThreadList> threadList(new ThreadList);
  for (auto i = begin; i != end; ++i)
    threadList->add(maker(*i));

  return std::move(threadList);
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_THREADLIST__
