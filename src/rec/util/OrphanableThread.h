#ifndef __REC_UTIL_ORPHANABLE_THREAD__
#define __REC_UTIL_ORPHANABLE_THREAD__

#include "juce_amalgamated.h"

namespace rec {
namespace util {

class OrphanableThread : public Thread {
 public:
  OrphanableThread() : orphaned_(false) {}

  virtual void run() {
    while (!threadShouldExit())
      loop();

    {
      ScopedLock l(lock_);
      if (!orphaned_)
        return;
    }
    delete this;
  }

  void orphan() {
    {
      ScopedLock l(lock_);
      if (isThreadRunning()) {
        orphaned_ = true;
        return;
      }
    }
    delete this;
  }

  virtual void loop() = 0;

 protected:
  CriticalSection lock_;

 private:
  bool orphaned_;
  DISALLOW_COPY_AND_ASSIGN(OrphanableThread);
};

}  // namespace util
}  // namespace rec

#endif __REC_UTIL_ORPHANABLE_THREAD__

