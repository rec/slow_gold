#ifndef __REC_UTIL_BLOCK_FILLSERIES__
#define __REC_UTIL_BLOCK_FILLSERIES__

#include "rec/util/block/Block.h"

namespace rec {
namespace util {
namespace block {

// Return a list of blocks from BlockSet with a total length length,
// starting at or after position;
BlockList wrapSeries(const BlockSet& selection, Size position, Size length);
BlockList fillSeries(const BlockSet& selection, Size position, Size length);

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_FILLSERIES__
