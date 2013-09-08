#ifndef __REC_UTIL_THREAD_MAKETHREAD__
#define __REC_UTIL_THREAD_MAKETHREAD__

#include "rec/util/thread/MakeCallback.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

class Thread : public juce::Thread, public OwnedPointer<Callback> {
 public:
  Thread(const String& name, Callback* r, int waitTime = 0)
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

  Thread* setWaitTime(int t) {
    waitTime_ = t;
    return this;
  }

 private:
  int waitTime_;
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Thread);
};

}  // namespace callback

inline unique_ptr<callback::Thread> makeThread(const String& name, Callback* cb) {
  return make_unique<callback::Thread>(name, cb);
}

template <typename Type>
unique_ptr<callback::Thread> makeThread(const String& name, Type o) {
  return make_unique<callback::Thread>(name, makeCallback<Type>>(o));
}

template <typename Type, typename Method>
unique_ptr<callback::Thread> makeThread(const String& name, Type* o, Method m) {
  return make_unique<callback::Thread>(name, methodCallback<Type, Method>>(o, m));
}

template <typename Type, typename Method, typename Value>
unique_ptr<callback::Thread> makeThread(const String& name, Type* o, Method m, Value v) {
  return make_unique<callback::Thread>(name, methodCallback<Type, Method, Value>>(o, m, v));
}

template <typename Type, typename Method, typename V1, typename V2>
unique_ptr<callback::Thread> makeThread(const String& name, Type* o, Method m, V1 v1, V2 v2) {
  return make_unique<callback::Thread>(name, methodCallback<Type, Method, V1, V2>>(o, m, v1, v2));
}

inline unique_ptr<callback::Thread> makeLoop(int waitTime, const String& name, Callback* cb) {
  return make_unique<callback::Thread>(name, cb, waitTime);
}

template <typename Type>
unique_ptr<callback::Thread> makeLoop(int t, const String& name, Type o) {
  return make_unique<callback::Thread>(name, makeCallback<Type>>(o), t);
}

template <typename Type, typename Method>
unique_ptr<callback::Thread> makeLoop(int t, const String& name, Type* o, Method m) {
  return make_unique<callback::Thread>(name, methodCallback<Type, Method>>(o, m), t);
}

template <typename Type, typename Method, typename Value>
unique_ptr<callback::Thread> makeLoop(int t, const String& name, Type* o, Method m, Value v) {
  return make_unique<callback::Thread>(name, methodCallback<Type, Method, Value>>(o, m, v), t);
}

template <typename Type, typename Method, typename V1, typename V2>
unique_ptr<callback::Thread> makeLoop(int t, const String& name, Type* o, Method m, V1 v1, V2 v2) {
  return make_unique<callback::Thread>(name, methodCallback<Type, Method, V1, V2>>(o, m, v1, v2), t);
}

inline callback::Thread& runInNewThread(const String& n, int p, unique_ptr<Callback> cb) {
  thread_ptr<callback::Thread> t(new callback::Thread(n, cb.release()));
  t->setPriority(p);
  t->startThread();
  trash::add(t.get());
  return *t.release();
}

template <typename Type>
callback::Thread& runInNewThread(const String& n, int p, Type o) {
  return runInNewThread(n, p, makeCallback<Type>(o));
}

template <typename Type, typename Method>
callback::Thread& runInNewThread(const String& n, int p, Type* o, Method m) {
  return runInNewThread(n, p, methodCallback<Type, Method>(o, m));
}

template <typename Type, typename Method, typename Value>
callback::Thread& runInNewThread(const String& n, int p, Type* o, Method m, Value v) {
  return runInNewThread(n, p, methodCallback<Type, Method, Value>(o, m, v));
}

template <typename Type, typename Method, typename V1, typename V2>
callback::Thread& runInNewThread(const String& n, int p, Type* o, Method m, V1 v1, V2 v2) {
  return runInNewThread(n, p, methodCallback<Type, Method, V1, V2>(o, m, v1, v2));
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_MAKETHREAD__
