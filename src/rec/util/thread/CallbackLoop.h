#ifndef __REC_THREAD_CALLBACKLOOP__
#define __REC_THREAD_CALLBACKLOOP__

#include "rec/base/base.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/RunnableThread.h"
#include "rec/util/thread/WaitLoop.h"

namespace rec {
namespace thread {

template <typename Type, typename Method>
Runnable* callbackLoop(int period, Type* obj, Method m, bool owns = false) {
  return new WaitLoop(period, makeCallback(obj, m, owns));
};

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_CALLBACKLOOP__
