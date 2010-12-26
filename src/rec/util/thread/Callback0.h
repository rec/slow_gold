#ifndef __REC_UTIL_THREAD_CALLBACK0__
#define __REC_UTIL_THREAD_CALLBACK0__

#include "rec/util/thread/Callback.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

template <typename Type, typename Method>
class Callback0 : public Callback {
 public:
  Callback0(Type* o, Method m) : object_(o), method_(m) {}
  virtual bool operator()() {
    (object_->*method_)();
    return true;
  }

 private:
  Type* object_;
  Method method_;
};

template <typename Type, typename Method>
class CallbackBool0 : public Callback {
 public:
  CallbackBool0(Type* o, Method m) : object_(o), method_(m) {}

  virtual bool operator()() { return (object_->*method_)(); }

 private:
  Type* object_;
  Method method_;
};

}  // namespace callback
}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_CALLBACK0__
