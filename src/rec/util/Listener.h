#ifndef __REC_UTIL_LISTENER__
#define __REC_UTIL_LISTENER__

#include <glog/logging.h>
#include <set>

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
class Listener {
 public:
  virtual void operator()(Type x) = 0;
  virtual ~Listener() {}
};

}  // namespace util
}  // namespace rec




#endif  // __REC_UTIL_LISTENER__
