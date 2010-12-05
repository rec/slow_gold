#ifndef __REC_UTIL_LISTENER_LISTENER__
#define __REC_UTIL_LISTENER_LISTENER__

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace listener {

template <typename Type>
class Listener {
 public:
  Listener() {}
  virtual ~Listener() {}
  virtual void operator()(Type x) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(Listener);
};

}  // namespace listener
}  // namespace util
}  // namespace rec




#endif  // __REC_UTIL_LISTENER_LISTENER__
