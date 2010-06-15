#include "juce_amalgamated.h"
#include "rec/audio/source/new/MergeBlockList.h"

namespace rec {
namespace buffer {

void merge(const Block& block, BlockSet* set) {
  BlockSet::iterator i = set->begin();
  for (; i != set->end() && i->second < block.first; ++i) {
    std::cout << "first " << i->first << ", " << i->second << "\n";
  }

  BlockSet::iterator begin = i;
  for (; i != set->end() && i->first <= block.second; ++i) {
    std::cout << "second " << i->first << ", " << i->second << "\n";
  }
  
  if (i == begin) {
    set->insert(i, block);

  } else {
    BlockSet::iterator end = i;
    end--;

    Size first = jmin(block.first, begin->first);
    Size second = jmax(block.second, end->second);
    set->erase(begin, i);
    set->insert(Block(first, second));
  }
}

}  // namespace buffer
}  // namespace rec
