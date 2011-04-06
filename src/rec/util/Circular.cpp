#include "rec/util/Circular.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

Circular::Circular(int64 bufferSize) {
  reset(0, bufferSize);
}

Circular::Circular(int64 begin, int64 bufferSize) {
  reset(begin, bufferSize);
}

void Circular::reset(int64 begin, int64 bufferSize) {
  begin_ = begin;
  filled_ = 0;
  if (bufferSize >= 0)
    bufferSize_ = bufferSize;
}

void Circular::fill(int64 delta) {
  filled_ += delta;
  if (filled_ > bufferSize_) {
    LOG(ERROR) << "Overfilled: " << filled_
               << ", " << bufferSize_;
    filled_ = bufferSize_;
  }
}

int64 Circular::remainingBlock() const {
  return bufferSize_ - std::max(filled_, end());
}

void Circular::setBegin(int64 begin) {
  int64 delta = begin - begin_;
  if (delta < 0)
    delta += bufferSize_;

  filled_ -= delta;
  if (filled_ < 0)
    filled_ = 0;

  begin_ = begin;
}

int64 Circular::end() const {
  return filledPosition(filled_);
}

int64 Circular::filledPosition(int x) const {
  return mod(begin_ + x, bufferSize_);
}

// How many samples are filled starting at begin?
int64 Circular::filledFrom(int64 begin) const {
  if (filled_ == bufferSize_)
    return filled_;

  if (begin <  begin_)
    begin += bufferSize_;

  return begin_ + filled_ - begin;
}

int64 Circular::consume(int64 amount) {
  begin_ = filledPosition(amount);
  if (amount > filled_) {
    LOG(ERROR) << "Tried to consume more than was filled: "
               << amount << ", " << filled_;
    amount = filled_;
  }
  filled_ -= amount;
  return amount;
}

}  // namespace util
}  // namespace rec
