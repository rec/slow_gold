#ifndef __REC_UTIL_THREAD_MAKECALLBACK__
#define __REC_UTIL_THREAD_MAKECALLBACK__

#include "rec/util/thread/Callback0.h"
#include "rec/util/thread/Callback1.h"
#include "rec/util/thread/Callback2.h"
#include "rec/util/thread/Pointer.h"

namespace rec {
namespace util {
namespace thread {

// Callbacks for functions or methods which return null.

template <typename Type>
Callback* makeCallback(Type o) {
  return new thread::callback::Pointer<Type>(o);
}

template <typename Type, typename Method>
Callback* makeCallback(Type* o, Method m) {
  return new thread::callback::Callback0<Type, Method>(o, m);
}

template <typename Function, typename Value>
Callback* functionCallback(Function f, Value v) {
  return new thread::callback::CallbackFunc1<Function, Value>(f, v);
}

template <typename Function, typename V1, typename V2>
Callback* functionCallback(Function f, V1 v1, V2 v2) {
  return new thread::callback::CallbackFunc1<Function, Value>(f, v1, v2);
}

template <typename Type, typename Method, typename Value>
Callback* makeCallback(Type* o, Method m, Value v) {
  return new thread::callback::Callback1<Type, Method, Value>(o, m, v);
}

template <typename Type, typename Method, typename V1, typename V2>
Callback* makeCallback(Type* o, Method m, V1 v1, V2 v2) {
  return new thread::callback::Callback2<Type, Method, V1, V2>(o, m, v1, v2);
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_MAKECALLBACK__
