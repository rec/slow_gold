#ifndef __REC_UTIL_THREAD_MAKETHREAD__
#define __REC_UTIL_THREAD_MAKETHREAD__

#include "rec/util/thread/MakeCallback.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

class Thread : public juce::Thread,
               public OwnedPointer<Callback> {
 public:
  Thread(const String& name, Callback* r = NULL)
      : juce::Thread(name), OwnedPointer<Callback>(r) {
  }
  virtual void run() { (*this)(); }
};

class Loop : public juce::Thread,
             public OwnedPointer<Callback> {
 public:
  Loop(const String& name, int waitTime, Callback* r = NULL)
      : Thread(name), OwnedPointer<Callback>(r), waitTime_(waitTime) {
  }

  virtual void run() {
    while (!threadShouldExit() && (*this)())
      wait(waitTime_);
  }

  static Loop* make(const String& name, int per, int prio, Callback* cb) {
    ptr<Loop> thread(new Loop(name, per, cb));
    thread->setPriority(prio);
    thread->startThread();
    return thread.transfer();
  }

  const int waitTime_;
};


}  // namespace callback

template <typename Type>
Thread* makeThread(const String& name, Type o) {
  return new thread::callback::Thread(name, makeCallback<Type>(o));
}

template <typename Type, typename Method>
Thread* makeThread(const String& name, Type* o, Method m) {
  return new thread::callback::Thread(name, makeCallback<Type, Method>(o, m));
}

template <typename Type, typename Method, typename Value>
Thread* makeThread(const String& name, Type* o, Method m, Value v) {
  return new thread::callback::Thread(name, makeCallback<Type, Method, Value>(o, m, v));
}

template <typename Type, typename Method, typename V1, typename V2>
Thread* makeThread(const String& name, Type* o, Method m, V1 v1, V2 v2) {
  return new thread::callback::Thread(name, makeCallback<Type, Method, V1, V2>(o, m, v1, v2));
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_MAKETHREAD__
