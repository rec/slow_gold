#ifndef __REC_UTIL_CLOCKUPDATE__
#define __REC_UTIL_CLOCKUPDATE__

#include "rec/base/base.h"

namespace rec {
namespace util {

struct ClockUpdate {
  float time_;
  float length_;

  ClockUpdate(float time, float length) : time_(time), length_(length) {}
  ClockUpdate() {}
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CLOCKUPDATE__
