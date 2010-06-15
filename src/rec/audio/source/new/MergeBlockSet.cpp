#include "juce_amalgamated.h"
#include "rec/audio/source/new/MergeBlockSet.h"

namespace rec {
namespace buffer {

void merge(const Block& block, BlockSet* set) {
  BlockSet::const_iterator i = set->begin();
  for (; i != set->end() && i->second < block.first; ++i);

  BlockSet::const_iterator begin = i;
  for (; i != set->end() && i->first <= block.second; ++i);

  if (i == begin) {
    set->insert(i, block);

  } else {
    BlockSet::const_iterator end = i;
    end--;

    Size first = jmin(block.first, begin->first);
    Size second = jmax(block.second, end->second);
    set->erase(begin, i);
    set->insert(Block(first, second));
  }
}

}  // namespace buffer
}  // namespace rec
