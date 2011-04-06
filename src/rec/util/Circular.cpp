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
  available_ = 0;
  if (bufferSize >= 0)
    bufferSize_ = bufferSize;
}

void Circular::fill(int64 delta) {
  delta = std::min(delta, bufferSize_ - available_);
  available_ += delta;
}

int64 Circular::remainingBlock() const {
  return bufferSize_ - std::max(available_, end());
}

int64 Circular::end() const {
  return filledPosition(available_);
}

int64 Circular::filledPosition(int x) const {
  return mod(begin_ + x, bufferSize_);
}

// How many samples are available starting at begin?
int64 Circular::availableFrom(int64 begin) const {
  if (available_ == bufferSize_)
    return available_;

  if (begin <  begin_)
    begin += bufferSize_;

  return begin_ + available_ - begin;
}

int64 Circular::consume(int64 amount) {
  begin_ = filledPosition(amount);
  if (amount > available_) {
    LOG(ERROR) << "Tried to consume more than was available: "
               << amount << ", " << available_;
    amount = available_;
  }
  available_ -= amount;
  return amount;
}

}  // namespace util
}  // namespace rec
