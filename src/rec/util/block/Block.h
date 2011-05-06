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
typedef int64 Size;

typedef std::pair<Size, Size> Block;
typedef std::vector<Block> BlockList;
typedef std::set<Block> BlockSet;

inline Block makeBlock(Size a, Size b) { return std::make_pair(a, b); }

inline Size getSize(const Block& b) {
  return b.second - b.first;
}

inline bool contains(const Block& b, Size x) {
  return (x >= b.first) && (x < b.second);
}

template <typename Container>
bool contains(const Container& c, Size x) {
  for (typename Container::const_iterator i = c.begin(); i != c.end(); ++i) {
    if (contains(*i, x))
      return true;
  }

  return false;
}
#if 0
inline bool contains(const BlockSet& bs, Size x) { return containsC(bs, x); }
inline bool contains(const BlockList& bs, Size x) { return containsC(bs, x); }
#endif
inline bool intersects(const Block& x, const Block& y) {
  return contains(x, y.first) || contains(y, x.first);
}

inline bool isBlock(const BlockSet& set, const Block& block) {
  return (set.size() == 1) && (*set.begin() == block);
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

inline AudioSourceChannelInfo audioSourceChannelInfo(
    const Block& block,
    AudioSampleBuffer* buf = NULL) {
  AudioSourceChannelInfo info;
  info.startSample = block.first;
  info.numSamples = getSize(block);
  info.buffer = buf;
  return info;
}

inline std::ostream& operator<<(std::ostream& os, const Block& b) {
  return os << "(" << b.first << ", " << b.second << ")";
}

inline std::ostream& operator<<(std::ostream& os, const BlockSet& b) {
  os << "{";
  for (BlockSet::const_iterator i = b.begin(); i != b.end(); ++i)
    os << *i << ", ";
  return os << "}";
}

inline std::ostream& operator<<(std::ostream& os, const BlockList& b) {
  os << "[";
  for (BlockList::const_iterator i = b.begin(); i != b.end(); ++i)
    os << *i << ", ";
  return os << "]";
}

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_BLOCK__
