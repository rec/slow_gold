#include "rec/util/range/Fillable.h"

#include "rec/util/range/Difference.h"
#include "rec/util/range/FullTo.h"
#include "rec/util/range/Merge.h"

namespace rec {
namespace util {

void Fillable::setNextFillPosition(SampleTime position) {
  DCHECK_GE(position, 0);
  DCHECK_LT(position, length_);
  Lock l(lock_);
  position_ = juce::jmin(length_, juce::jmax(position, SampleTime(0)));
}

void Fillable::setLength(SampleTime length) {
  Lock l(lock_);
  length_ = length;
}

SampleTime Fillable::length() const {
  Lock l(lock_);
  return length_;
}

SampleTime Fillable::position() const {
  Lock l(lock_);
  return position_;
}

double Fillable::filledPercent() const {
  Lock l(lock_);
  return static_cast<double>(filled_.size()) / length_;
}

bool Fillable::hasFilled(const SampleRange& b) const {
  Lock l(lock_);
  if (isFull())
    return true;

  if (b.end_ <= length_)
    return difference<SampleTime>(b, filled_).empty();

  return hasFilled(SampleRange(b.begin_, length_)) &&
    hasFilled(SampleRange(0, b.end_ - length_));
}

bool Fillable::isFull() const {
  Lock l(lock_);
  return (util::fullTo<SampleTime>(filled_) == length_);
}

void Fillable::reset() {
  Lock l(lock_);
  filled_.clear();
  position_ = 0;
}

SampleTime Fillable::fillNextBlock() {
  Lock l(lock_);
  if (isFull())
    return 0;

  SampleRange range = firstEmptyRangeAfter<SampleTime>(filled_, position_, length_);

  if (range.size() <= 0) {
    LOG(DFATAL) << "Getting an empty range";
    return 0;
  }

  if (SampleTime size = doFillNextBlock(range)) {
    range.end_ = range.begin_ + size;
    filled_ = merge<SampleTime>(filled_, range);
    if (isFull())
      onFilled();
    position_ += size;
    if (position_ > length_)
      position_ -= length_;
    return size;
  }

  LOG(DFATAL) << "Couldn't fill range";
  return 0;
}

}  // namespace util
}  // namespace rec

