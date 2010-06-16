#ifndef __REC_BLOCKS
#define __REC_BLOCKS

#include "stddef.h"

#include <algorithm>
#include <set>
#include <vector>

namespace rec {
namespace block {

/** The size of a block. */
typedef size_t Size;

typedef std::pair<Size, Size> Block;
typedef std::vector<Block> BlockList;
typedef std::set<Block> BlockSet;

inline Size getSize(const Block& b) { return b.second - b.first; }
inline bool covers(const Block& a, const Block& b) {
  return a.first <= b.first && a.second >= b.second;
}

Block getNextBlock(const BlockSet& set, const Block& requested);
void merge(BlockSet* set, const Block& block);
bool covers(const BlockSet& set, const Block& block);

}  // namespace block
}  // namespace rec

#endif  // __REC_BLOCKS
