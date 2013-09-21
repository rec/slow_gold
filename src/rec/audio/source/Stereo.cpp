#include "rec/audio/source/Stereo.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

namespace {

StereoProto::Value getValue(const StereoProto& stereo) {
  auto type = stereo.type();
  if (type == StereoProto::PASSTHROUGH)
    return StereoProto::UNCHANGED;

  auto side = stereo.side();
  if (side == StereoProto::LEFT)
    return StereoProto::LEFT_ONLY;

  if (side == StereoProto::RIGHT)
    return StereoProto::RIGHT_ONLY;

  if (side == StereoProto::LEFT_PLUS_RIGHT)
    return StereoProto::LEFT_AND_RIGHT;

  if (type == StereoProto::FLIP)
    return StereoProto::FLIP_POLARITY;

  if (type == StereoProto::CENTER_ELIMINATION)
    return StereoProto::ELIMINATE_CENTER;

  if (type == StereoProto::CENTER_ELIMINATION_MONO)
    return StereoProto::ELIMINATE_CENTER_MONO;
  LOG(DFATAL) << "Couldn't decipher StereoProto " << stereo.ShortDebugString();

  return StereoProto::UNCHANGED;
}

}  // namespace

Stereo::Stereo(PositionableAudioSource* source, const StereoProto& desc)
    : Wrappy(source) {
  setStereo(desc);
}

void fixStereo(StereoProto* stereo) {
  if (not stereo->has_value())
    stereo->set_value(getValue(*stereo));
  stereo->clear_type();
  stereo->clear_side();
}

void Stereo::setStereo(const StereoProto& desc) {
  Lock l(lock_);
  desc_ = desc;
  fixStereo(&desc_);
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
  StereoProto::Value value = desc.value();

  source()->getNextAudioBlock(info);
  if (value == StereoProto::UNCHANGED)
    return;

  if (info.buffer->getNumChannels() != 2) {
    LOG(DFATAL) << "wrong number of channels";
    return;
  }

  AudioSampleBuffer& b = *info.buffer;
  int n = b.getNumSamples();

  if (value == StereoProto::LEFT_AND_RIGHT) {
    b.applyGain(StereoProto::RIGHT, 0, n, 0.5f);
    b.addFrom(StereoProto::RIGHT, 0, b, StereoProto::LEFT, 0, n, 0.5f);
    b.copyFrom(StereoProto::LEFT, 0, b, StereoProto::RIGHT, 0, n);

  } else if (value == StereoProto::LEFT_ONLY) {
    b.copyFrom(1, 0, b, 0, 0, n);

  } else if (value == StereoProto::RIGHT_ONLY) {
    b.copyFrom(0, 0, b, 1, 0, n);

  } else if (value == StereoProto::FLIP_POLARITY) {
    b.applyGain(0, 0, n, -1.0f);

  } else {
    b.addFrom(0, 0, b, 1, 0, n, -1.0f);
    b.applyGain(0, 0, n, 0.5f);

    if (value == StereoProto::ELIMINATE_CENTER)
      b.addFrom(1, 0, b, 0, 0, n, -1.0f);

    else if (value == StereoProto::ELIMINATE_CENTER_MONO)
      b.copyFrom(1, 0, b, 0, 0, n);
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
