#include "rec/audio/source/BufferSource.h"
#include "rec/audio/util/FillableBuffer.h"

namespace rec {
namespace audio {
namespace source {

void BufferSource::getNextAudioBlock(const Info& i) {
  BufferTime from(const_cast<Buffer*>(buffer_), position_);
  BufferTime to(i.buffer, i.startSample);

  for (SamplePosition toCopy = i.numSamples; toCopy > 0; ) {
    SamplePosition t = std::min<int64>(getTotalLength() - position_, toCopy);

    copy(from, to, t);
    toCopy -= t;
    to.time_ += t;

    setNextReadPosition(position_ + t);
    from.time_ = position_;
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
