#ifndef __REC_BLOCKS
#define __REC_BLOCKS

#include "stddef.h"

#include <algorithm>
#include <set>
#include <vector>

namespace rec {
namespace buffer {

/** The size of a buffer. */
typedef size_t Size;

typedef std::pair<Size, Size> Block;
typedef std::vector<Block> BlockList;
typedef std::set<Block> BlockSet;

inline Block makeBlock(Size a, Size b) { return std::make_pair(a, b); }
inline Size getSize(const Block& b) { return b.second - b.first; }

}  // namespace buffer
}  // namespace rec

#endif  // __REC_BLOCKS
