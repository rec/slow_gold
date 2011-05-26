#include "rec/util/thread/MakeThread.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

namespace {

class CallbackThread : public juce::Thread, public OwnedPointer<Callback> {
 public:
  CallbackThread(const String& name, Callback* r, int waitTime = 0)
      : juce::Thread(name), OwnedPointer<Callback>(r), waitTime_(waitTime) {
  }

  virtual void run() {
    while (!threadShouldExit() && (*this)()) {
      if (!waitTime_)
        break;

      if (!threadShouldExit())
        wait(waitTime_);
    }
  }

 private:
  int waitTime_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(CallbackThread);
};

}  // namespace 
}  // namespace callback


Thread* makeThread(const String& name, Callback* cb) {
  return new callback::CallbackThread(name, cb);
}

Thread* runInNewThread(const String& n, int p, Callback* cb) {
  thread_ptr<Thread> t(makeThread(n, cb));
  t->setPriority(p);
  t->startThread();
  trash::add(t.get());
  return t.transfer();
}

Thread* makeLoop(int waitTime, const String& name, Callback* cb) {
  return makeThread(name, cb, waitTime);
}


}  // namespace thread
}  // namespace util
}  // namespace rec
