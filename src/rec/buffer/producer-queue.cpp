#include <algorithm>
#include <functional>

#include "rec/buffer/producer-queue.h"

using std::for_each;
using std::bind2nd;
using std::mem_fun;

namespace rec {
namespace buffer {

void ProducerQueue::allocate(Size size, BlockList* blocks) {
  Size begin = 0;
  BlockSet::const_iterator i;
  for (i = all_.begin(); i != all_.end() && size > 0; ++i) {
    if (i->begin_ > begin) {
      Size blockSize = std::min(i->size(), size);
      blocks->push_back(Block(begin, blockSize));
      size -= blockSize;
    }
    begin = i->end_;
  }

  if (size > 0)
    blocks->push_back(Block(begin, begin + size));

  production_.insert(production_.end(), blocks->begin(), blocks->end());
  all_.insert(blocks->begin(), blocks->end());
}

BlockList ProducerQueue::produce(const Block& block) {
  BlockList blocks;
  produced_.insert(block);
  BlockList::iterator i = production_.begin();
  for (; i != production_.end() && (produced_.find(*i) != produced_.end()); ++i)
    produced_.erase(*i);

  blocks.insert(blocks.end(), production_.begin(), i);
  production_.erase(production_.begin(), i);

  return blocks;
}

void ProducerQueue::remove(const BlockList& blocks) {
  for (BlockList::const_iterator i = blocks.begin(); i != blocks.end(); ++i)
    all_.erase(*i);

  // for_each(blocks.begin(), blocks.end(),
  //          bind1st(std::mem_fun(&BlockSet::erase), all_));
}

}  // namespace buffer
}  // namespace rec
