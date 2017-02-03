#pragma once

#include "rec/util/thread/Callback.h"
#include "rec/util/thread/Callback1.h"
#include "rec/util/thread/Callback2.h"
#include "rec/util/thread/Callback3.h"
#include "rec/util/thread/Callback4.h"
#include "rec/util/thread/MakeCallback.h"

namespace rec {
namespace util {
namespace thread {

template <typename Type>
unique_ptr<Callback> functionCB(Type o) {
  return makeCallback(o);
}

template <typename Function, typename Value>
unique_ptr<Callback> functionCB(Function f, Value v) {
  return std::make_unique<callback::CallbackFunc1<Function, Value>>(f, v);
}

template <typename Function, typename V1, typename V2>
unique_ptr<Callback> functionCB(Function f, V1 v1, V2 v2) {
  return std::make_unique<callback::CallbackFunc2<Function, V1, V2>>(f, v1, v2);
}

template <typename Function, typename V1, typename V2, typename V3>
unique_ptr<Callback> functionCB(Function f, V1 v1, V2 v2, V3 v3) {
  return std::make_unique<callback::CallbackFunc3<Function, V1, V2, V3>>(f, v1, v2, v3);
}

template <typename Function, typename V1, typename V2, typename V3, typename V4>
unique_ptr<Callback> functionCB(Function f, V1 v1, V2 v2, V3 v3, V4 v4) {
  return std::make_unique<callback::CallbackFunc4<Function, V1, V2, V3, V4>>(f, v1, v2, v3, v4);
}

}  // namespace thread
}  // namespace util
}  // namespace rec
