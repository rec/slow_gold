#include "JuceLibraryCode/JuceHeader.h"
#include "rec/base/basictypes.h"
#include "rec/util/block/Block.h"
#include "rec/util/block/GetNextBlock.h"

namespace rec {
namespace util {
namespace block {

Block getNextBlock(const Block& requested, const BlockSet& set) {
  Block block = requested;

  // upper is the first element that starts above the given block's beginning.
  BlockSet::const_iterator upper = set.upper_bound(requested);
  Size top = (upper == set.end()) ? kint64max : upper->first;

  if (upper != set.begin()) {
    --upper;  // This is now the last element whose block is below this one.
    block.first = juce::jmax(block.first, upper->second);
    // block.second = block.first + getSize(requested);
  }

  block.second = juce::jmin(block.second, top);
  return block;
}

BlockSet difference(const BlockSet& set, const Block& block) {
  BlockSet diff;
  Block b = block;
  BlockSet::const_iterator i;
  for (i = set.begin(); i != set.end() && getSize(b) > 0; ++i) {
    if (i->second > b.first) {
      if (i->first > b.first)
        diff.insert(Block(b.first, juce::jmin(b.second, i->first)));
      b.first = i->second;
    }
  }

  return diff;
}


}  // namespace block
}  // namespace util
}  // namespace rec
