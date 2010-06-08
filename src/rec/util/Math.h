#ifndef __REC_UTIL_MATH
#define __REC_UTIL_MATH

#include "rec/base/types.h"

namespace rec {
namespace util {

template <typename Number> Number abs(Number x) { return (x < 0) ? -x : x; }

// A arithmetic modulus function that's always non-negative.
// See http://en.wikipedia.org/wiki/Modulo_operation#cite_note-0
//
template <typename Number>
inline Number mod(Number dividend, Number divisor) {
  Number modulo = dividend % divisor;
  return (modulo < 0) ? (modulo + abs(divisor)) : modulo;
}

template <typename Items>
struct Range {
  Items begin_;
  Items end_;

  int length() { return end_ - begin_; }
};

struct Circular {
  int64 size_;
  int64 position_;

  Circular() {}
  Circular(int64 size, int64 position = 0) : size_(size), position_(position) {}

  void increment(int64 delta) {
    position_ = mod(position_ + delta, size_);
  }

  void scale(double scale) {
    size_ = int64(scale * size_);
    position_ = int64(scale * position_);
  }

  // The number of positions remaining in the circular buffer.
  // This is always between 1 and size_, inclusive.
  int64 remaining() const { return size_ - position_; }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_MATH
