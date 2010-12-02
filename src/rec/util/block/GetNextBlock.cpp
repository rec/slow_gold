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

}  // namespace block
}  // namespace util
}  // namespace rec
