#include "rec/audio/source/Stereo.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

void Stereo::setType(Type type) {
  ScopedLock l(lock_);
  type_ = type;
}

void Stereo::setSide(Side side) {
  ScopedLock l(lock_);
  side_ = side;
}

void Stereo::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  source()->getNextAudioBlock(info);
  if (type_ == PASSTHROUGH || info.buffer->getNumChannels() != 2)
    return;

  AudioSampleBuffer& b = *info.buffer;
  int n = b.getNumSamples();
  if (type_ == SINGLE) {
    b.copyFrom(RIGHT - side_, 0, b, side_, 0, n);

  } else if (type_ == INVERT) {
    b.applyGain(side_, 0, n, -1.0);

  } else {
    b.addFrom(side_, 0, b, RIGHT - side_, 0, n, -1.0);
    b.applyGain(side_, 0, n, 0.5);

    if (type_ == CENTER_ELIMINATION)
      b.addFrom(RIGHT - side_, 0, b, side_, 0, n, -1.0);
    else
      b.copyFrom(RIGHT - side_, 0, b, side_, 0, n);
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
