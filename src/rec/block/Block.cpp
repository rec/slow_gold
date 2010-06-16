#include "juce_amalgamated.h"
#include "rec/base/basictypes.h"
#include "rec/block/Block.h"

namespace rec {
namespace block {

namespace {

typedef BlockSet::const_iterator iterator;

}  // namespace

Block getNextBlock(const BlockSet& set, const Block& requested) {
  Block block = requested;

  iterator upper = set.upper_bound(requested);
  Size top = (upper == set.end()) ? kint64max : upper->first;

  if (upper != set.begin()) {
    --upper;
    block.first = jmax(block.first, upper->second);
    block.second = block.first + getSize(requested);
  }

  block.second = jmin(block.second, top);
  return block;
}

void merge(BlockSet* set, const Block& block) {
  // "begin" is the first block that isn't entirely below the new block.
  iterator begin = set->begin();
  for (; begin != set->end() && begin->second < block.first; ++begin);

  // "end" is the first block that's entirely above the new block.
  // "last" is one before "end"
  iterator last, end = begin;
  for (; end != set->end() && end->first <= block.second; last = end, ++end);

  if (begin == end) {
    // We don't intersect or touch any existing blocks, so insert this block.
    set->insert(end, block);

  } else {

    // This block intersects or touches every block in [begin, end).
    Size first = jmin(block.first, begin->first);
    Size second = jmax(block.second, last->second);
    set->erase(begin, end);
    set->insert(Block(first, second));
  }
}

bool covers(const BlockSet& set, const Block& b) {
  for (iterator i = set.begin(); i != set.end(); ++i)
    if (covers(*i, b))
      return true;

  return false;
}

}  // namespace block
}  // namespace rec
