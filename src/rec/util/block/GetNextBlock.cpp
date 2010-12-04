#include "rec/util/block/Block.h"
#include "rec/util/block/GetNextBlock.h"

namespace rec {
namespace util {
namespace block {

Block getNextBlock(const Block& requested, const BlockSet& set) {
  Block ret = requested;
  BlockSet diff = difference(set, requested);
  if (diff.empty()) {
    ret.first = ret.second;
  } else {
    ret.first = diff.begin()->first;
    ret.second = diff.rbegin()->second;
  }

  return ret;
}

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

  if (getSize(b))
    diff.insert(b);

  return diff;
}


}  // namespace block
}  // namespace util
}  // namespace rec
