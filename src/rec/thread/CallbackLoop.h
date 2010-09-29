#ifndef __REC_THREAD_CALLBACKLOOP__
#define __REC_THREAD_CALLBACKLOOP__

#include "rec/base/base.h"
#include "rec/thread/Callback.h"
#include "rec/thread/RunnableThread.h"
#include "rec/thread/WaitLoop.h"

namespace rec {
namespace thread {

template <typename Type, typename Method>
Runnable* callbackLoop(int period, Type* object, Method method) {
  return new WaitLoop(period, makeCallback(object, method));
};

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_CALLBACKLOOP__
