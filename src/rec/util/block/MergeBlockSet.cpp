#include "JuceLibraryCode/JuceHeader.h"
#include "rec/util/block/MergeBlockSet.h"

namespace rec {
namespace util {
namespace block {

void merge(const Block& block, BlockSet* set) {
  // "begin" is the first block that isn't entirely below the new block.
  BlockSet::const_iterator begin = set->begin();
  for (; begin != set->end() && begin->second < block.first; ++begin);

  // "end" is the first block that's entirely above the new block.
  BlockSet::const_iterator end = begin;
  for (; end != set->end() && end->first <= block.second; ++end);

  if (begin == end) {
    // We don't intersect or touch any existing blocks, so insert this block.
    set->insert(end, block);

  } else {
    // This block intersects or touches every block in [begin, end).
    Size first = juce::jmin(block.first, begin->first);
    Size second = juce::jmax(block.second, (--end)->second);

    set->erase(begin, ++end);
    set->insert(Block(first, second));
  }
}

void merge(const BlockSet& b, BlockSet* set) {
  for (BlockSet::const_iterator i = b.begin(); i != b.end(); ++i)
    merge(*i, set);
}


}  // namespace block
}  // namespace util
}  // namespace rec
