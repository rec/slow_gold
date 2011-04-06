#ifndef __REC_UTIL_CIRCULAR__
#define __REC_UTIL_CIRCULAR__

#include "rec/util/block/Block.h"
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
  void consume(int64 amount);

  bool isFull() const { return filled_ == bufferSize_; }

  int64 remainingBlock() const;

  block::Block nextBlockToFill(int64 maxBlockSize) const;

  void setBegin(int64 begin);

  int64 filled() const { return filled_; }
  int64 length() const { return bufferSize_; }

  int64 begin() const { return begin_; }
  int64 end() const;

 private:
  int64 filledPosition(int x) const;

  int64 begin_;
  int64 filled_;  // Of this region within the buffer.
  int64 bufferSize_;
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
