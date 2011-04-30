#ifndef __REC_THREAD_CALLBACK__
#define __REC_THREAD_CALLBACK__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace thread {
namespace callback {

// A generic callback.
class Callback {
 public:
  virtual bool operator()() = 0;
  virtual ~Callback() {}
};

}  // namespace callback
}  // namespace thread
}  // namespace util
}  // namespace rec

#include "Pointer.h"

#endif  // __REC_THREAD_CALLBACK__
