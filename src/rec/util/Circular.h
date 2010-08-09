#ifndef __REC_UTIL_CIRCULAR__
#define __REC_UTIL_CIRCULAR__

#include "rec/base/types.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

// A region within a circular buffer of a fixed size.  Note that begin_ might be
// greater than end_, which means that the region wraps around.  An empty
// region has begin_ == end_;  by convention, a region representing the entire
// block always has begin_ = 0, end_ = size_.
struct Circular {
  int64 begin_;
  int64 end_;
  int64 size_;

  Circular() {}
  Circular(int64 begin, int64 size)
      : begin_(begin), end_(begin), size_(size) {
  }

  bool increment(int64 delta) {
    if (delta >= remaining()) {
      begin_ = 0;
      end_ = size_;
      return false;
    } else {
      end_ = mod(end_ + delta, size_);
      return true;
    }
  }

/*
  void scale(double scale) {
    size_ = int64(scale * size_);
    position_ = int64(scale * position_);
  }*/

  // The number of elements used in this buffer.
  int64 diameter() const {
    return (end_ >= begin_) ? (end_ - begin_) : (end_ - begin_ + size_);
  }

  int64 remaining() const { return size_ - diameter(); }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
