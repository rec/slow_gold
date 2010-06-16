#ifndef __REC_UTIL_CIRCULAR__
#define __REC_UTIL_CIRCULAR__

#include "rec/base/types.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

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

#endif  // __REC_UTIL_CIRCULAR__
