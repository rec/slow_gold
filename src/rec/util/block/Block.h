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

// The size of a buffer.
// TODO:  size_t is unsigned which makes for weirdnesses.  Change to signed!
typedef size_t Size;

typedef std::pair<Size, Size> Block;
typedef std::vector<Block> BlockList;
typedef std::set<Block> BlockSet;

inline Block makeBlock(Size a, Size b) { return std::make_pair(a, b); }

inline Size getSize(const Block& b) {
  return (b.second > b.first) ? (b.second - b.first) : 0;
}

inline bool isBlock(const BlockSet& set, const Block& block) {
  return set.size() == 1 && *set.begin() == block;
}

inline int fullTo(const BlockSet& set) {
  return (set.empty() || set.begin()->first) ? 0 : set.begin()->second;
}

inline BlockSet slice(const Block& b, int length) {
  BlockSet s;
  if (b.second <= length) {
    s.insert(b);
  } else {
    s.insert(Block(b.first, length));
    s.insert(Block(0, b.second - length));
  }
  return s;
}

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_BLOCK__
