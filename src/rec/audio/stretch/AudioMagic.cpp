#include "rec/audio/stretch/AudioMagic.h"
#include "rec/audio/ammf_scaler/AudioTimeScaler.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/stretch/Stretchy.h"

namespace rec {
namespace audio {
namespace stretch {

AudioMagic::AudioMagic(PositionableAudioSource* s, const Stretch& stretch)
    : Implementation(s) {
  setStretch(stretch);
}

AudioMagic::~AudioMagic() {}

void AudioMagic::setStretch(const Stretch& stretch) {
  channels_ = stretch.channels();
  outOffset_.resize(channels_);
  scaler_.reset(new AudioTimeScaler);

  if (const char* err = scaler_->Init(timeScale(stretch),
                                      stretch.sample_rate(),
                                      channels_,
                                      pitchScale(stretch),
                                      stretch.bands(),
                                      stretch.filter_overlap()))
    LOG(ERROR) << err;
}

void AudioMagic::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  int zeroCount = 0;
  for (AudioSourceChannelInfo i = info; i.numSamples; ) {
    if (int processed = static_cast<int>(processOneChunk(i))) {
      if (zeroCount) {
        LOG_FIRST_N(ERROR, 20) << "Got it on try " << (zeroCount + 1);
      }

      i.numSamples -= processed;
      i.startSample += processed;
      zeroCount = 0;
    } else {
      CHECK_LT(++zeroCount, 10);
    }
  }
}

int64 AudioMagic::processOneChunk(const AudioSourceChannelInfo& info) {
  int inSampleCount = scaler_->GetInputBufferSize(info.numSamples) / 2;
	float** samples = getSourceSamples(inSampleCount);
  for (int c = 0; c < channels_; ++c)
    outOffset_[c] = info.buffer->getSampleData(c) + info.startSample;

  return scaler_->Process(samples, &outOffset_.front(),
                          inSampleCount, info.numSamples);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

