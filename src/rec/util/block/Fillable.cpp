#include "rec/util/block/Fillable.h"

#include "rec/util/block/Difference.h"
#include "rec/util/block/MergeBlockSet.h"

namespace rec {
namespace util {
namespace block {

void Fillable::setPosition(int position) {
  ScopedLock l(lock_);
  position_ = position;
}

bool Fillable::hasFilled(const Block& b) const {
  ScopedLock l(lock_);
  if (isFull())
    return true;

  if (b.second <= length_)
    return difference(filled_, b).empty();

  return hasFilled(Block(b.first, length_)) &&
    hasFilled(Block(0, b.second - length_));
}

bool Fillable::isFull() const {
  ScopedLock l(lock_);
  return (fullTo(filled_) == length_);
}

void Fillable::fillNextBlock() {
  ScopedLock l(lock_);
  if (isFull())
    return;

  Block block = firstEmptyBlockAfter(filled_, position_, length_);
  {
    ScopedUnlock u(lock_);
    int numSamples = getSize(block);
    if (numSamples <= 0) {
      LOG(ERROR) << "Getting an empty block";
      return;
    }
    block.second = doFillNextBlock(block);
  }

  merge(block, &filled_);
  if (isFull())
    onFilled();
}

#if 0
bool waitUntilFilled(const Fillable& filler, const Block& block,
                     int maxWaitTime, int waitTime) {
  Thread* thread = Thread::getCurrentThread();
  for (int time = 0; !thread->threadShouldExit(); time += waitTime) {
    if (filler.hasFilled(block))
      return true;

    if (time > maxWaitTime) {
      LOG(ERROR) << "Waited for a long time, no data: " << time;
      return false;
    }

    if (waitTime > 0)
      thread->wait(waitTime);
  }
  return false;
}
#endif

}  // namespace block
}  // namespace util
}  // namespace rec

