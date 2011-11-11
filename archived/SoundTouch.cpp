#include "rec/audio/stretch/SoundTouch.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/soundtouch/SoundTouch.h"

namespace rec {
namespace audio {
namespace stretch {

SoundTouch::SoundTouch(PositionableAudioSource* s,
                                       const Stretch& stretch)
    : Implementation(s), buffer_(2, INPUT_BUFFER_SAMPLES) {
  fetchInfo_.numSamples = INPUT_BUFFER_SAMPLES;
  fetchInfo_.startSample = 0;
  fetchInfo_.buffer = &buffer_;
  frames_.setLength(INPUT_BUFFER_SAMPLES);
  setStretch(stretch);
}

SoundTouch::~SoundTouch() {}

void SoundTouch::setStretch(const Stretch& stretch) {
  if (!soundTouch_)
    soundTouch_.reset(new soundtouch::SoundTouch);
  soundTouch_->setRate(static_cast<float>(timeScale(stretch)));
  soundTouch_->setChannels(stretch.channels());
  soundTouch_->setPitch(pitchScale(stretch));
}

void SoundTouch::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  fillInput(info.numSamples);
  copyToOutput(info);
}

bool SoundTouch::fillInput(int numSamples) {
  static const int MAXIMUM_FAILURE_COUNT = 10;
  for (int fail = 0, s; (s = soundTouch_->numSamples()) && s < numSamples; ) {
    putSamples(fetchInfo_);
    if (s == soundTouch_->numSamples()) {
      if (++fail > MAXIMUM_FAILURE_COUNT) {
        LOG(ERROR) << "Made no progress in pitch shifter";
        return false;
      }
    } else {
      fail = 0;
    }
  }
  return true;
}

void SoundTouch::putSamples(const AudioSourceChannelInfo& info) {
  // source()->getNextAudioBlock(info);
  FloatFrame* frame = frames_.frames();
  for (int i = 0; i < info.numSamples; ++i, ++frame) {
    for (int c = 0; c < 2; ++c)
      frame->sample_[c] = *buffer_.getSampleData(c, i);
  }

  soundTouch_->putSamples(frames_.frames()->sample_, info.numSamples);
}

void SoundTouch::copyToOutput(const AudioSourceChannelInfo& info) {
  int n = info.numSamples;
  if (frames_.length() < n)
    frames_.setLength(n);
  uint rec = soundTouch_->receiveSamples(frames_.frames()->sample_, n);

  if (static_cast<int>(rec) != n)
    LOG(ERROR) << "Expected " << n << " got " << rec;

  FloatFrame* frame = frames_.frames();
  for (int i = 0; i < n; ++i, ++frame) {
    for (int c = 0; c < 2; ++c)
      *info.buffer->getSampleData(c, i) = frame->sample_[c];
  }
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

