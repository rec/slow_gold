#include "juce_amalgamated.h"
#include "rec/audio/source/new/MergeBlockSet.h"

namespace rec {
namespace buffer {

void merge(const Block& block, BlockSet* set) {
  // Find the first block that isn't entirely below the new block.
  BlockSet::const_iterator begin = set->begin();
  for (; begin != set->end() && begin->second < block.first; ++begin);

  BlockSet::const_iterator last, end = begin;

  // Find the first block that's entirely above the new block.
  for (; end != set->end() && end->first <= block.second; last = end, ++end);

  if (begin == end) {
    // We don't intersect or touch any existing blocks, so insert this block.
    set->insert(end, block);

  } else {
    // This block intersects or touches every block between begin and end.
    Size first = jmin(block.first, begin->first);
    Size second = jmax(block.second, last->second);
    set->erase(begin, end);
    set->insert(Block(first, second));
  }
}

}  // namespace buffer
}  // namespace rec
