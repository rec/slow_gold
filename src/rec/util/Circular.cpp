#include "rec/util/Circular.h"

namespace rec {
namespace util {

Circular::Circular(int64 begin, int64 length) : length_(length) {
  reset(begin);
}

void Circular::reset(int64 begin) {
  reset(begin, length_);
}

void Circular::reset(int64 begin, int64 length) {
  begin_ = begin;
  filled_ = 0;
  length_ = length;
}

bool Circular::fill(int64 delta) {
  delta = std::min(delta, remaining());
  filled_ += delta;
  return filled_ < length_;
}

int64 Circular::remaining() const { return length_ - filled_; }
int64 Circular::remainingBlock() const {
  return std::min(remaining(), length_ - end());
}

int64 Circular::begin()          const { return begin_; }
int64 Circular::end() const { return mod(begin_ + filled_, length_); }

// How many samples are available starting at begin?
int64 Circular::availableFrom(int64 begin) const {
  if (filled_ == length_)
    return filled_;

  if (begin <  begin_)
    begin += length_;

  return begin_ + filled_ - begin;
}

}  // namespace util
}  // namespace rec
