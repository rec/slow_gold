#ifndef __REC_BUFFER_SERVICES
#define __REC_BUFFER_SERVICES

#include "rec/util/locker.h"
#include "rec/uti/math.h"
#include "rec/buffer/blocks.h"

namespace rec {
namespace buffer {

// We assume the following generic services for any buffer types.
// TODO(tritchford): how to handle errors - use a return code or exceptions?
template <typename Buffer>
class Services {
 public:
  /** Try to expand or collapse a buffer to a given size, return the actual size
   *  that was allocated. */
  static Size setSize(Buffer buffer, Size size);

  /** Try to copy a block buffer of one type to a buffer of another type.
   *  Return the number of bytes actually copied. */
  template <typename BufferIn>
  static Size copy(Buffer out, Size outBegin,
                   BufferIn in, const Block& inBlock);
};

}  // namespace buffer
}  // namespace rec

#endif  // __REC_BUFFER_SERVICES
