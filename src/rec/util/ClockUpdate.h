#ifndef __REC_UTIL_CLOCKUPDATE__
#define __REC_UTIL_CLOCKUPDATE__

#include "rec/base/base.h"

namespace rec {
namespace util {

struct ClockUpdate {
  double time_;
  double length_;

  ClockUpdate(double time, double length) : time_(time), length_(length) {}
  ClockUpdate() {}

  template <typename Type>
  void update(Type *t) const {
    if (time_ >= 0)
      t->setTime(time_);
    if (length_ >= 0)
      t->setLength(length_);
  }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CLOCKUPDATE__
