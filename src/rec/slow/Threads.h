#ifndef __REC_SLOW_THREADS__
#define __REC_SLOW_THREADS__

#include "rec/slow/HasInstance.h"
#include "rec/util/HasLock.h"
#include "rec/util/thread/Looper.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/CallbackQueue.h"
#include "rec/util/HasLock.h"

namespace rec {
namespace slow {

class Threads : public HasInstance, public HasLock {
 public:
  static const int LOOP_TIME = 100;

  explicit Threads(Instance* i);
  ~Threads();

  void start();
  void clean();
  void queueCallback(void* owner, Callback* c);
  void removeCallbacksFor(void* owner);
  int runQueue();

 private:
  void stop();

  template <typename Operator>
  Thread* start(Operator op, const String& name, int priority = 0);

  struct ThreadList;
  ptr<ThreadList> threads_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
