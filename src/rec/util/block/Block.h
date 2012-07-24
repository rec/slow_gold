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

inline bool empty(const Block& b) {
  return (b.second == b.first);
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

inline Size compare(const Block& x, const Block& y) {
  if (Size d = x.first - y.first)
    return d;
  else
    return x.second - y.second;
}

inline Size compare(const BlockSet& x, const BlockSet& y) {
  BlockSet::const_iterator i = x.begin();
  BlockSet::const_iterator j = y.begin();

  for (;;) {
    if (i == x.end())
      return (j == y.end()) ? 0 : -1;

    if (j == y.end())
      return 1;

    if (Size c = compare(*i++, *j++))
      return c;
  }
}

inline bool intersects(const Block& x, const Block& y) {
  return contains(x, y.first) || contains(y, x.first);
}

inline Size getSize(const BlockSet& set) {
  Size size = 0;
  for (BlockSet::const_iterator i = set.begin(); i != set.end(); ++i)
    size += getSize(*i);

  return size;
}

inline bool isBlock(const BlockSet& set, const Block& block) {
  return (set.size() == 1) && (*set.begin() == block);
}

inline Block toBlock(const BlockSet& set) {
  Block b = makeBlock(0, 0);
  if (set.begin() != set.end()) {
    b.first = set.begin()->first;
    b.second = set.rbegin()->second;
  }
  return b;
}

inline Size fullTo(const BlockSet& set) {
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
  info.startSample = static_cast<int>(block.first);  // TODO: bug Jules about this!
  info.numSamples = static_cast<int>(getSize(block));
  info.buffer = buf;
  return info;
}

inline std::ostream& print(std::ostream& os, const Block& b) {
  return os << "(" << b.first << ", " << b.second << ")";
}

inline std::ostream& print(std::ostream& os, const BlockSet& b) {
  os << "{";
  for (BlockSet::const_iterator i = b.begin(); i != b.end(); ++i)
    print(os, *i) << ", ";
  return os << "}";
}

inline std::ostream& print(std::ostream& os, const BlockList& b) {
  os << "[";
  for (BlockList::const_iterator i = b.begin(); i != b.end(); ++i)
    print(os, *i) << ", ";
  return os << "]";
}

inline std::ostream& operator<<(std::ostream& os, const Block& b) {
  return print(os, b);
}

inline std::ostream& operator<<(std::ostream& os, const BlockSet& b) {
  return print(os, b);
}

inline std::ostream& operator<<(std::ostream& os, const BlockList& b) {
  return print(os, b);
}

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BLOCK_BLOCK__
