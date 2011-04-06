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

bool Circular::fill(int64 delta) {
  delta = std::min(delta, remaining());
  filled_ += delta;
  return filled_ < bufferSize_;
}

int64 Circular::remaining() const {
  return bufferSize_ - filled_;
}

int64 Circular::remainingBlock() const {
  return std::min(remaining(), bufferSize_ - end());
}

int64 Circular::end() const {
  return filledPosition(filled_);
}

int64 Circular::filledPosition(int x) const {
  return mod(begin_ + x, bufferSize_);
}

// How many samples are available starting at begin?
int64 Circular::availableFrom(int64 begin) const {
  if (filled_ == bufferSize_)
    return filled_;

  if (begin <  begin_)
    begin += bufferSize_;

  return begin_ + filled_ - begin;
}

int64 Circular::consume(int64 amount) {
  begin_ = filledPosition(amount);
  filled_ = mod(filled_ - amount, bufferSize_);
  return amount;
}

}  // namespace util
}  // namespace rec
