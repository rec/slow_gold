#ifndef __REC_UTIL_BLOCK_FILLSERIES__
#define __REC_UTIL_BLOCK_FILLSERIES__

#include "rec/util/block/Block.h"

namespace rec {
namespace util {
namespace block {

// Return a list of blocks from BlockSet that fill the size of block,
// starting at or after the start of block.
BlockList fillSeries(const BlockSet& selection, Size position, Size length);

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_FILLSERIES__
