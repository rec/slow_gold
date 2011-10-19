#ifndef __REC_UTIL_THREAD_FUNCTIONCALLBACK__
#define __REC_UTIL_THREAD_FUNCTIONCALLBACK__

#include "rec/util/thread/Callback.h"
#include "rec/util/thread/Callback1.h"
#include "rec/util/thread/Callback2.h"

namespace rec {
namespace util {
namespace thread {

template <typename Type>
Callback* functionCallback(Type o) {
  return makeCallback(o);
}

template <typename Function, typename Value>
Callback* functionCallback(Function f, Value v) {
  return new callback::CallbackFunc1<Function, Value>(f, v);
}

template <typename Function, typename V1, typename V2>
Callback* functionCallback(Function f, V1 v1, V2 v2) {
  return new callback::CallbackFunc2<Function, V1, V2>(f, v1, v2);
}

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_FUNCTIONCALLBACK__
