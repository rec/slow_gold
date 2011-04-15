#include "rec/audio/source/BufferSource.h"

namespace rec {
namespace audio {
namespace source {

BufferSource::BufferSource(const Buffer& buffer)
    : buffer_(buffer), position_(0), looping_(true) {
}

void BufferSource::getNextAudioBlock(const Info& i) {
  BufferTime from(const_cast<Buffer*>(&buffer_), position_);
  BufferTime to(i.buffer, i.startSample);

  for (SampleTime toCopy = i.numSamples; toCopy > 0; ) {
    SampleTime t = std::min(getTotalLength() - position_, toCopy);

    copy(from, to, t);
    toCopy -= t;
    to.time_ += t;

    setNextReadPosition(position_ + t);
    from.time_ = position_;
  }
}

void BufferSource::setNextReadPosition(int64 p) {
  position_ = mod(p, getTotalLength());
}

}  // namespace source
}  // namespace audio
}  // namespace rec
