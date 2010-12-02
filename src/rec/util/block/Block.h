#ifndef __REC_UTIL_BLOCK_BLOCK__
#define __REC_UTIL_BLOCK_BLOCK__

#include "stddef.h"

#include <algorithm>
#include <set>
#include <vector>

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace block {

/** The size of a buffer. */
typedef size_t Size;

typedef std::pair<Size, Size> Block;
typedef std::vector<Block> BlockList;
typedef std::set<Block> BlockSet;

inline Block makeBlock(Size a, Size b) { return std::make_pair(a, b); }
inline Size getSize(const Block& b) { return b.second - b.first; }

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_BLOCK__
