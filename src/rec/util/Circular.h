#ifndef __REC_UTIL_CIRCULAR__
#define __REC_UTIL_CIRCULAR__

#include "rec/base/types.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

// A region within a circular buffer of a fixed size.
struct Circular {
 public:
  Circular() {}
  Circular(int64 begin, int64 length) : length_(length) { reset(begin); }

  void reset(int64 begin) {
    begin_ = begin;
    size_ = 0;
  }

  bool increment(int64 delta) {
    delta = std::min(delta, remaining());
    size_ += delta;
    return size_ < length_;
  }

  int64 remaining()      const { return length_ - size_; }
  int64 remainingBlock() const { return std::min(remaining(), length_ - end()); }

  int64 begin()          const { return begin_; }
  int64 end()            const { return mod(begin_ + size_, length_); }

  // How many samples are available starting at begin?
  int64 availableFrom(int64 begin) const {
    if (size_ == length_)
      return size_;

    if (begin <  begin_)
      begin += length_;

    return begin_ + size_ - begin;
  }

 private:
  int64 begin_;
  int64 size_;  // Of this region within the buffer.
  const int64 length_;  // Of the whole buffer.

  // This class is copiable and assignable.
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
