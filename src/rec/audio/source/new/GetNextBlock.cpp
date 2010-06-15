#include "juce_amalgamated.h"
#include "rec/base/basictypes.h"
#include "rec/buffer/blocks.h"
#include "rec/audio/source/new/GetNextBlock.h"

namespace rec {
namespace buffer {

Block getNextBlock(const Block& requested, const BlockSet& set) {
  Block block = requested;
  BlockSet::const_iterator upper = set.upper_bound(requested);
  Size top = (upper == set.end()) ? kint64max : upper->first;
  if (upper != set.begin()) {
    --upper;
    block.first = jmax(block.first, upper->second);
    block.second = block.first + getSize(requested);
  }
  block.second = jmin(block.second, top);
  return block;
}

}  // namespace buffer
}  // namespace rec
