#ifndef __REC_UTIL_LISTENER_LISTENER__
#define __REC_UTIL_LISTENER_LISTENER__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace listener {

template <typename Type>
class Listener {
 public:
  virtual void operator()(Type x) = 0;
  virtual ~Listener() {}
};

}  // namespace listener
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_LISTENER_LISTENER__
