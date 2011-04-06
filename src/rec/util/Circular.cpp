#include "rec/util/Circular.h"
#include "rec/util/Math.h"

namespace rec {
namespace util {

using block::Block;

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

void Circular::consume(int64 amount) {
  begin_ = filledPosition(amount);
  if (amount > filled_) {
    LOG(ERROR) << "Tried to consume more than was filled: "
               << amount << ", " << filled_;
    amount = filled_;
  }
  filled_ -= amount;
}

Block Circular::nextBlockToFill(int64 maxBlockSize) const {
  int64 begin = end();
  int64 size = std::min(maxBlockSize, bufferSize_ - filled_);
  return Block(begin, std::min(bufferSize_, begin + size));
}

}  // namespace util
}  // namespace rec
