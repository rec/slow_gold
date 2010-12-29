#include "rec/util/Circular.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

Circular::Circular(int64 length) {
  reset(0, length);
}

Circular::Circular(int64 begin, int64 length) {
  reset(begin, length);
}

void Circular::reset(int64 begin, int64 length) {
  begin_ = begin;
  filled_ = 0;
  if (length >= 0)
    length_ = length;
}

bool Circular::fill(int64 delta) {
  delta = std::min(delta, remaining());
  filled_ += delta;
  return filled_ < length_;
}

int64 Circular::remaining() const {
  return length_ - filled_;
}

int64 Circular::remainingBlock() const {
  return std::min(remaining(), length_ - end());
}

int64 Circular::end() const { return fromBegin(filled_); }
int64 Circular::fromBegin(int x) const { return mod(begin_ + x, length_); }

// How many samples are available starting at begin?
int64 Circular::availableFrom(int64 begin) const {
  if (filled_ == length_)
    return filled_;

  if (begin <  begin_)
    begin += length_;

  return begin_ + filled_ - begin;
}

int64 Circular::consume(int64 amount) {
  begin_ = fromBegin(amount);
  filled_ = mod(filled_ - amount, length_);
  return amount;
}

}  // namespace util
}  // namespace rec
