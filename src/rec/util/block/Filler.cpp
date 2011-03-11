#include "rec/util/block/Filler.h"

#include "rec/util/block/Difference.h"
#include "rec/util/block/MergeBlockSet.h"

namespace rec {
namespace util {
namespace block {

void Filler::setPosition(int position) {
  ScopedLock l(lock_);
  position_ = position;
}

bool Filler::hasFilled(const Block& b) const {
  ScopedLock l(lock_);
  if (isFull())
    return true;

  if (b.second <= length_)
    return difference(filled_, b).empty();

  return hasFilled(Block(b.first, length_)) &&
    hasFilled(Block(0, b.second - length_));
}

bool Filler::isFull() const {
  ScopedLock l(lock_);
  return (fullTo(filled_) == length_);
}

void Filler::fillNextBlock() {
  Block block;
  {
    ScopedLock l(lock_);
    block = firstEmptyBlockAfter(filled_, position_, length_);
  }

  int numSamples = getSize(block);
  if (numSamples <= 0) {
    LOG(ERROR) << "Getting an empty block";
    return;
  }

  doFillNextBlock(block);
}

bool Filler::waitUntilFilled(const Block& block, int waitTime, int maxTime) {
  Thread* thread = Thread::getCurrentThread();
  for (int time = 0; !thread->threadShouldExit(); time += waitTime) {
    if (hasFilled(block))
      return true;

    if (time > maxTime) {
      LOG(ERROR) << "Waited for a long time, no data: " << time;
      return false;
    }
    if (waitTime > 0)
      thread->wait(waitTime);
  }
  return false;
}

}  // namespace block
}  // namespace util
}  // namespace rec
