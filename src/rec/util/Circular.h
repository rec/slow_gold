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

  void reset(int64 begin) { reset(begin, length_); }

  void reset(int64 begin, int64 length) {
    begin_ = begin;
    filled_ = 0;
    length_ = length;
  }

  bool fill(int64 delta) {
    delta = std::min(delta, remaining());
    filled_ += delta;
    return filled_ < length_;
  }

  int64 remaining()      const { return length_ - filled_; }
  int64 remainingBlock() const { return std::min(remaining(), length_ - end()); }

  int64 begin()          const { return begin_; }
  int64 end()            const { return mod(begin_ + filled_, length_); }

  // How many samples are available starting at begin?
  int64 availableFrom(int64 begin) const {
    if (filled_ == length_)
      return filled_;

    if (begin <  begin_)
      begin += length_;

    return begin_ + filled_ - begin;
  }

 private:
  int64 begin_;
  int64 filled_;  // Of this region within the buffer.
  int64 length_;  // Of the whole buffer.

  // This class is copiable and assignable.
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
