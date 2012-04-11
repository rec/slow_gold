#include "rec/audio/source/Stereo.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

void Stereo::setStereo(const StereoProto& desc) {
  Lock l(lock_);
  desc_ = desc;
}

StereoProto Stereo::getStereo() const {
  Lock l(lock_);
  return desc_;
}

void Stereo::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  StereoProto desc;
  {
    Lock l(lock_);
    desc = desc_;
  }
  StereoProto::Type type = desc.type();
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
  StereoProto::Side side = desc.side();
  StereoProto::Side otherSide = static_cast<StereoProto::Side>(
      StereoProto::RIGHT - side);

  DCHECK_GE(side, StereoProto::LEFT);
  DCHECK_LE(side, StereoProto::LEFT_PLUS_RIGHT);

  if (type == StereoProto::SINGLE) {
    if (side == StereoProto::LEFT_PLUS_RIGHT) {
      b.applyGain(StereoProto::RIGHT, 0, n, 0.5f);
      b.addFrom(StereoProto::RIGHT, 0, b, StereoProto::LEFT, 0, n, 0.5f);
      b.copyFrom(StereoProto::LEFT, 0, b, StereoProto::RIGHT, 0, n);

    } else {
      b.copyFrom(otherSide, 0, b, side, 0, n);
    }

  } else if (type == StereoProto::FLIP) {
    b.applyGain(side, 0, n, -1.0f);

  } else {
    side = StereoProto::LEFT;
    otherSide = StereoProto::RIGHT;
    b.addFrom(side, 0, b, otherSide, 0, n, -1.0f);
    b.applyGain(side, 0, n, 0.5f);

    if (type == StereoProto::CENTER_ELIMINATION)
      b.addFrom(otherSide, 0, b, side, 0, n, -1.0f);

    else if (type == StereoProto::CENTER_ELIMINATION_MONO)
      b.copyFrom(otherSide, 0, b, side, 0, n);

  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
