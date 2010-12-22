#ifndef __REC_THREAD_CALLBACK__
#define __REC_THREAD_CALLBACK__

#include "rec/base/base.h"
#include "rec/util/thread/Runnable.h"

namespace rec {
namespace util {
namespace thread {

template <typename Type, typename Return=bool>
class Callback : public Runnable {
 public:
  typedef Return (Type::*Method)();
  Callback(Type* obj, Method m) : object_(obj), method_(m) {}

  virtual ~Callback() {}
  virtual Return run(Thread*) {
    return (object_->*method_)();
  }

 private:
  Type* object_;
  Method method_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Callback);
};

template <typename Type>
class AsyncCallback : public juce:: CallbackMessage {
 public:
  typedef void (Type::*Method)();
  AsyncCallback(Type* obj, Method m) : object_(obj), method_(m) {}
  virtual ~AsyncCallback() {}

  virtual void messageCallback() {
    (object_->*method_)();
  }

 private:
  Type* object_;
  Method method_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AsyncCallback);
};

template <typename Type, typename Method>
Runnable* makeCallback(Type* object, Method method) {
  return new Callback<Type>(object, method);
}

template <typename Type, typename Method>
void callAsync(Type* object, Method method) {
  (new AsyncCallback<Type>(object, method))->post();
}


}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_CALLBACK__
