#include "rec/util/block/Block.h"
#include "rec/util/block/Difference.h"

namespace rec {
namespace util {
namespace block {

namespace {
typedef BlockSet::const_iterator iterator;
}

BlockSet difference(const Block& block, const BlockSet& s) {
  BlockSet diff;
  Block b = block;
  iterator i;
  for (i = s.begin(); i != s.end() && getSize(b) && b.second > i->first; ++i) {
    if (b.first < i->second) {
      if (b.first < i->first) {
        diff.insert(Block(b.first, i->first));
        b.first = i->first;
      }

      if (b.second > i->first) {
        if (b.second <= i->second)
          b.second = i->second;
      }
      b.first = i->second;
    }
  }

  if (getSize(b) > 0)
    diff.insert(b);

  return diff;
}

BlockSet difference(const BlockSet& x, const BlockSet& y) {
  BlockSet result;
  for (iterator i = x.begin(), j = y.begin(); i != x.end(); ++i) {
    for (; j != y.end() && j->second <= i->first; ++j);
    Block b = *i;
    for (; j != y.end() && j->first < i->second; ++j) {
      if (i->first < j->first)
        result.insert(Block(b.first, j->first));
      b.first = j->second;
    }
    if (getSize(b) > 0)
      result.insert(b);
  }

  return result;
}

Block firstEmptyBlockAfter(const BlockSet& s, int64 pos, int64 length) {
  BlockSet diff = difference(Block(pos, length), s);
  if (diff.empty())
    diff = difference(Block(0, pos), s);

  return diff.empty() ? Block(pos, pos) : *diff.begin();
}

}  // namespace block
}  // namespace util
}  // namespace rec
