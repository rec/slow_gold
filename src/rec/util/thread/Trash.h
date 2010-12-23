#ifndef __REC_UTIL_THREAD_TRASH__
#define __REC_UTIL_THREAD_TRASH__

#include <set>

#include "rec/base/base.h"
#include "rec/util/STL.h"

namespace rec {
namespace util {
namespace thread {
namespace trash {

void discard(Thread* t);

template <typename ThreadClass>
void discard(ptr<ThreadClass>* t) {
  discard(t->transfer());
}

void empty();
void waitForAllThreadsToExit(int timeout);
inline void discardAndEmpty(Thread* t) { discard(t); empty(); }

}  // namespace trash
}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_TRASH__
