#ifndef __REC_SLOW_THREADS__
#define __REC_SLOW_THREADS__

#include "rec/util/HasLock.h"
#include "rec/util/thread/Looper.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/CallbackQueue.h"
#include "rec/util/HasLock.h"

namespace rec { namespace util { namespace thread { class ThreadList; }}}

namespace rec {
namespace slow {

class Threads : public HasLock {
 public:
  Threads();
  ~Threads();

  Thread* guiThread();
  Thread* timerThread();
  Thread* updateThread();

  void start();
  int runQueue();

 private:
  void clean();
  void queueCallback(void* owner, Callback* c);
  void removeCallbacksFor(void* owner);
  void stop();

  template <typename Operator>
  Thread* start(Operator op, const String& name, int priority = 0);

  struct ThreadList;
  ptr<ThreadList> threads_;
  ptr<util::thread::ThreadList> threads2_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
