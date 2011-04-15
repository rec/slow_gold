#include "rec/audio/source/CircularBuffer.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

SampleTime CircularBuffer::fullFrom(SampleTime x) const {
  SampleTime result = 0;
  if (x > range_.begin_)
    if (range_.end_ > range_.begin_)
      result = range_.end - x;
    else
      result = capacity() - x;
      return
      return

    return isFull_ ? capacity() - x : x;
  else
    return
}

void CircularBuffer::fill(SampleTime toFill) {
  SampleTime unfilled = isFull_ ? 0 : getNumSamples() - size();
  if (toFill > unfilled)
    LOG(ERROR) << "toFill=" << toFill << " > unfilled=" << unfilled;

  isFull_ = (toFill >= unfilled);
  range_.end_ = isFull_ ? range_.begin_ : mod(range_.end_ + toFill);
}

void CircularBuffer::consume(SampleTime toConsume) {
  SampleTime filled = filledSize();
  if (toConsume > filled) {
    LOG(ERROR) << "toConsume=" << toConsume << " > filled=" << filled;
    toConsume = filled;
  }
  range_.begin_ = mod(range_.begin + toConsume);
  if (toConsume)
    isFull_ = false;
}

}  // namespace source
}  // namespace audio
}  // namespace rec

