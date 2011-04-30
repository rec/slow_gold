#ifndef __REC_SLOW_THREADS__
#define __REC_SLOW_THREADS__

#include "rec/slow/HasInstance.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace slow {

struct ThreadData;

class Threads : public HasInstance {
 public:
  static const int LOOP_TIME = 100;

  explicit Threads(Instance* i);
  ~Threads();
  void startAll();
  void stop();
  CriticalSection* lock() { return &lock_; }
  ThreadData* data() { return data_.get(); }

 private:
  typedef std::vector<Thread*> ThreadList;
  typedef void (*InstanceFunction)(Instance*);

  Thread* start(InstanceFunction f, const String& name,
                int waitTime = LOOP_TIME);

  ThreadList threads_;
  CriticalSection lock_;
  ptr<ThreadData> data_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
