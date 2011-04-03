#include "rec/audio/source/Stereo.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

void Stereo::setDesc(const StereoProto& desc) {
  ScopedLock l(lock_);
  desc_ = desc;
}

void Stereo::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  StereoProto::Type type = desc_.type();
  DCHECK_GE(type, StereoProto::PASSTHROUGH);
  DCHECK_LE(type, StereoProto::CENTER_ELIMINATION_MONO);

  source()->getNextAudioBlock(info);
  if (type == StereoProto::PASSTHROUGH)
    return;

  DCHECK_EQ(info.buffer->getNumChannels(), 2);
  if (info.buffer->getNumChannels() != 2)
    return;

  AudioSampleBuffer& b = *info.buffer;
  int n = b.getNumSamples();
  StereoProto::Side side = desc_.side();
  StereoProto::Side otherSide = static_cast<StereoProto::Side>(
      StereoProto::RIGHT - side);

  DCHECK_GE(side, StereoProto::LEFT);
  DCHECK_LE(side, StereoProto::LEFT_PLUS_RIGHT);

  if (type == StereoProto::SINGLE) {
    if (side == StereoProto::LEFT_PLUS_RIGHT) {
      b.applyGain(StereoProto::RIGHT, 0, n, 0.5);
      b.addFrom(StereoProto::RIGHT, 0, b, StereoProto::LEFT, 0, n, 0.5);
      b.copyFrom(StereoProto::LEFT, 0, b, StereoProto::RIGHT, 0, n);

    } else {
      b.copyFrom(otherSide, 0, b, side, 0, n);
    }

  } else if (type == StereoProto::INVERT) {
    b.applyGain(side, 0, n, -1.0);

  } else {
    b.addFrom(side, 0, b, otherSide, 0, n, -1.0);
    b.applyGain(side, 0, n, 0.5);

    if (type == StereoProto::CENTER_ELIMINATION)
      b.addFrom(otherSide, 0, b, side, 0, n, -1.0);

    else if (type == StereoProto::CENTER_ELIMINATION_MONO)
      b.copyFrom(otherSide, 0, b, side, 0, n);

  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
