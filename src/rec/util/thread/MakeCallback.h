#ifndef __REC_UTIL_THREAD_MAKECALLBACK__
#define __REC_UTIL_THREAD_MAKECALLBACK__

#include "rec/util/thread/Callback0.h"
#include "rec/util/thread/Callback1.h"
#include "rec/util/thread/Callback2.h"

namespace rec {
namespace util {
namespace thread {

// Callbacks for functions or methods which return null.

template <typename Type>
Callback* makeCallback(Type o) {
  return new thread::callback::Pointer<Type>(o);
}

#if 0
template <typename Value>
Callback* makeCallback(void (*f)(Value),  Value v) {
  return new thread::callback::FunctionValue(f, v);
}
#endif

template <typename Type, typename Method>
Callback* makeCallback(Type* o, Method m) {
  return new thread::callback::Callback0<Type, Method>(o, m);
}

template <typename Type, typename Method, typename Value>
Callback* makeCallback(Type* o, Method m, Value v) {
  return new thread::callback::Callback1<Type, Method, Value>(o, m, v);
}

template <typename Type, typename Method, typename V1, typename V2>
Callback* makeCallback(Type* o, Method m, V1 v1, V2 v2) {
  return new thread::callback::Callback2<Type, Method, V1, V2>(o, m, v1, v2);
}


// Callbacks for methods that return something that can cast to a bool.

template <typename Type>
Callback* makeCallbackBool(Type o) {
  return new thread::callback::PointerBool<Type>(o);
}

template <typename Type, typename Method>
Callback* makeCallbackBool(Type* o, Method m) {
  return new thread::callback::CallbackBool0<Type, Method>(o, m);
}

template <typename Type, typename Method, typename Value>
Callback* makeCallbackBool(Type* o, Method m, Value v) {
  return new thread::callback::CallbackBool1<Type, Method, Value>(o, m, v);
}

template <typename Type, typename Method, typename V1, typename V2>
Callback* makeCallbackBool(Type* o, Method m, V1 v1, V2 v2) {
  return new thread::callback::CallbackBool2<Type, Method, V1, V2>(o, m, v1, v2);
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_MAKECALLBACK__
