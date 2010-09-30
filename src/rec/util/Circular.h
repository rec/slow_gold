#ifndef __REC_UTIL_CIRCULAR__
#define __REC_UTIL_CIRCULAR__

#include "rec/base/base.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

// A region within a circular buffer of a fixed size.
struct Circular {
 public:
  Circular() {}
  Circular(int64 begin, int64 length);

  void reset(int64 begin);
  void reset(int64 begin, int64 length);
  bool fill(int64 delta);

  int64 remaining()      const;
  int64 remainingBlock() const;

  int64 begin()          const;
  int64 end()            const;

  // How many samples are available starting at begin?
  int64 availableFrom(int64 begin) const;

 private:
  int64 begin_;
  int64 filled_;  // Of this region within the buffer.
  int64 length_;  // Of the whole buffer.

  // This class is copiable and assignable.
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CIRCULAR__
