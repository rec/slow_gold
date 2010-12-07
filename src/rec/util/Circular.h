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
  bool fill(int64 delta);

  int64 remaining() const;
  int64 remainingBlock() const;

  // How many samples are available starting at begin?
  int64 availableFrom(int64 begin) const;
  int begin() const { return begin_; }
  int64 end() const;
  // int64 setEnd(int64 end) { end_ = restrict(end); }

  int64 fromBegin(int x) const;
  int64 consume(int64 amount);

  int64 filled() const { return filled_; }

  // Return an index restricted to the circular buffer..
  int64 restrict(int64 x) const { return mod(x, length_); }

 private:
  int64 begin_;
  int64 filled_;  // Of this region within the buffer.
  int64 length_;  // Of the whole buffer.

  DISALLOW_COPY_AND_ASSIGN(Circular);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
