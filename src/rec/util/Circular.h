#ifndef __REC_UTIL_CIRCULAR__
#define __REC_UTIL_CIRCULAR__

#include "rec/base/base.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

// A region within a circular buffer of a fixed size.
struct Circular {
 public:
  explicit Circular(int64 length = 0);
  explicit Circular(int64 begin, int64 length);

  void reset(int64 begin = 0, int64 length = -1);

  void fill(int64 delta);
  bool isFull() const { return available_ == bufferSize_; }

  int64 remainingBlock() const;

  // How many samples are available starting at begin?
  int64 availableFrom(int64 begin) const;
  int begin() const { return begin_; }
  int64 end() const;

  int64 consume(int64 amount);

  int64 filled() const { return available_; }
  int64 length() const { return bufferSize_; }

 private:
  int64 filledPosition(int x) const;

  int64 begin_;
  int64 available_;  // Of this region within the buffer.
  int64 bufferSize_;
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
