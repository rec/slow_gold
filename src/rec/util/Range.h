#ifndef __REC_UTIL_RANGE__
#define __REC_UTIL_RANGE__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
struct Range {
  Range() {}
  Range(Type b, Type e) : begin_(b), end_(e) {}

  Type begin_;
  Type end_;

  int size() const { return end_ - begin_; }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE__
