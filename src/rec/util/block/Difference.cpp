#include "rec/util/block/Block.h"
#include "rec/util/block/Difference.h"

namespace rec {
namespace util {
namespace block {

BlockSet difference(const BlockSet& s, const Block& block) {
  BlockSet diff;
  Block b = block;
  BlockSet::const_iterator i;
  for (i = s.begin(); i != s.end() && b.second > i->first; ++i) {
    if (b.first < i->second) {
      if (b.first < i->first) {
        diff.insert(Block(b.first, i->first));
        b.first = i->first;
      }

      if (b.second > i->first) {
        if (b.second <= i->second)
          b.second = i->first;
      }
      b.first = i->second;
    }
  }

  if (getSize(b) > 0)
    diff.insert(b);

  return diff;
}

// TODO: this is quadratic
BlockSet difference(const BlockSet& set, const BlockSet& set2) {
  BlockSet result = set;
  for (BlockSet::const_iterator i = set2.begin(); i != set2.end(); ++i)
    result = difference(set, *i);

  return result;
}

Block firstEmptyBlockAfter(const BlockSet& s, int pos, int length) {
  BlockSet diff = difference(s, Block(pos, length));
  if (diff.empty())
    diff = difference(s, Block(0, pos));

  return diff.empty() ? Block(pos, pos) : *diff.begin();
}

}  // namespace block
}  // namespace util
}  // namespace rec
