#ifndef __REC_THREAD_CALLBACKLOOP__
#define __REC_THREAD_CALLBACKLOOP__

#include "rec/base/base.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/RunnableThread.h"
#include "rec/util/thread/WaitLoop.h"

namespace rec {
namespace util {
namespace thread {

template <typename Type, typename Method>
CallbackMessage* callbackLoop(int period, Type* obj, Method m) {
  return new WaitLoop(period, makeCallback(obj, m));
};

}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_THREAD_CALLBACKLOOP__
