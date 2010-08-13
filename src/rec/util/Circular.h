#ifndef __REC_UTIL_CIRCULAR__
#define __REC_UTIL_CIRCULAR__

#include "rec/base/types.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

// A region within a circular buffer of a fixed size.  Note that begin_ might be
// greater than end_, which means that the region wraps around.  An empty
// region has begin_ == end__.
struct Circular {
 public:
  Circular() {}
  Circular(int64 begin, int64 length)
      : begin_(begin), size_(0), length_(length) {
  }

  bool increment(int64 delta) {
    delta = std::min(delta, remaining());
    size_ += delta;
    return size_ < length_;
  }

  bool wrapsAround()     const { return (begin_ + size_) > length_; }
  int64 remaining()      const { return length_ - size_; }
  int64 remainingBlock() const { return length_ - std::max(size_,  begin_); }

  int64 begin()          const { return begin_; }
  int64 end()            const { return mod(begin_ + size_, length_); }

  bool contains(int begin, int size) const {
    if (begin <  begin_)
      begin += length_;

    return (begin + size) <= (begin_ + size_);
  }

 private:
  int64 begin_;
  int64 size_;  // Of this region within the buffer.
  int64 length_;  // Of the whole buffer.

  // This class is copiable and assignable.
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
