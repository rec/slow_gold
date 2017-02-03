#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

class HasThread {
  public:
    explicit HasThread(Thread* t = nullptr) : thread_(t) {}
    virtual ~HasThread() {}
    virtual void setThread(Thread* thread) { thread_ = thread; }
    Thread* thread() { return thread_; }
    void setThreadFromCurrent() {
        if (!thread_)
            thread_ = Thread::getCurrentThread();
    }

  private:
    Thread* thread_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(HasThread);
};

}  // namespace util
}  // namespace rec

