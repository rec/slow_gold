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
  source()->getNextAudioBlock(info);
  StereoProto::Type type = desc_.type();

  if (type == StereoProto::PASSTHROUGH)
    return;

  DCHECK_NE(info.buffer->getNumChannels(), 2);
  if (info.buffer->getNumChannels() != 2)
    return ;

  AudioSampleBuffer& b = *info.buffer;
  int n = b.getNumSamples();
  StereoProto::Side side = desc_.side();

  if (type == StereoProto::SINGLE) {
    b.copyFrom(StereoProto::RIGHT - side, 0, b, side, 0, n);

  } else if (type == StereoProto::INVERT) {
    b.applyGain(side, 0, n, -1.0);

  } else {
    b.addFrom(side, 0, b, StereoProto::RIGHT - side, 0, n, -1.0);
    b.applyGain(side, 0, n, 0.5);

    if (type == StereoProto::CENTER_ELIMINATION)
      b.addFrom(StereoProto::RIGHT - side, 0, b, side, 0, n, -1.0);
    else
      b.copyFrom(StereoProto::RIGHT - side, 0, b, side, 0, n);
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
