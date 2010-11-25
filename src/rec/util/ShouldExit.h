#ifndef __REC_UTIL_SHOULDEXIT__
#define __REC_UTIL_SHOULDEXIT__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Thread>
bool shouldExit(Thread* thread) {
  return thread && thread->threadShouldExit();
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_SHOULDEXIT__
