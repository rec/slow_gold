#ifndef __REC_UTIL_RANGE__
#define __REC_UTIL_RANGE__

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Type>
struct Range {
  Range() {}
  Range(Type b) : begin_(b), end_(b + 1) {}
  Range(Type b, Type e) : begin_(b), end_(e) {}

  bool operator==(const Range& x) const {
    return begin_ == x.begin && end_ == x.end_;
  }
  bool operator<(const Range& x) const {
    return begin_ < x.begin || (begin_ == x.begin && end_ < x.end_);
  }

  bool operator<=(const Range& x) const { return !(x < *this); }
  bool operator>(const Range& x) const { return x < *this; }
  bool operator>=(const Range& x) const { return x <= *this; }
  bool operator!=(const Range& x) const { return !(x == *this); }

  Type begin_;
  Type end_;

  Type size() const { return end_ - begin_; }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE__
