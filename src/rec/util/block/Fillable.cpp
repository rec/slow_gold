#include "rec/util/block/Fillable.h"

#include "rec/util/block/Difference.h"
#include "rec/util/block/MergeBlockSet.h"

namespace rec {
namespace util {
namespace block {

void Fillable::setNextFillPosition(int64 position) {
  DCHECK_GE(position, 0);  // TODO: why did this fire once?
  Lock l(lock_);
  position_ = juce::jmax(position, 0LL);
}

void Fillable::setLength(int64 length) {
  Lock l(lock_);
  length_ = length;
}

int64 Fillable::length() const {
  Lock l(lock_);
  return length_;
}

int64 Fillable::position() const {
  Lock l(lock_);
  return position_;
}

double Fillable::filledPercent() const {
  Lock l(lock_);
  return static_cast<double>(getSize(filled_)) / length_;
}

bool Fillable::hasFilled(const Block& b) const {
  Lock l(lock_);
  if (isFull())
    return true;

  if (b.second <= length_)
    return difference(b, filled_).empty();

  return hasFilled(Block(b.first, length_)) &&
    hasFilled(Block(0, b.second - length_));
}

bool Fillable::isFull() const {
  Lock l(lock_);
  return (fullTo(filled_) == length_);
}

int64 Fillable::fillNextBlock() {
  Lock l(lock_);
  if (isFull())
    return 0;

  Block block = firstEmptyBlockAfter(filled_, position_, length_);

  if (getSize(block) <= 0) {
    LOG(DFATAL) << "Getting an empty block";
    return 0;
  }

  if (int64 size = doFillNextBlock(block)) {
    block.second = block.first + size;
    merge(block, &filled_);
    if (isFull())
      onFilled();
    position_ += size;
    if (position_ > length_)
      position_ -= length_;
    return size;
  }

  LOG(DFATAL) << "Couldn't fill block";
  return 0;
}

}  // namespace block
}  // namespace util
}  // namespace rec

