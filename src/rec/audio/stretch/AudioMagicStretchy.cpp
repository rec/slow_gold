#include "rec/audio/stretch/AudioMagicStretchy.h"
#include "rec/audio/ammf_scaler/AudioTimeScaler.h"

namespace rec {
namespace audio {
namespace stretch {

namespace {

class AudioMagicStretchy : public source::Stretchy {
 public:
  static const int SAMPLE_BUFFER_SIZE = 1000;

  AudioMagicStretchy(PositionableAudioSource* s, const Stretch& stretch)
      : Stretchy(s, stretch), scaler_(new AudioTimeScaler) {
  }

  void initializeStretcher() {
    outOffset_.resize(stretch_.channels());
    scaler_.reset(new AudioTimeScaler);

    if (!buffer_ || buffer_->getNumChannels() != stretch_.channels())
      buffer_.reset(new Buffer(stretch_.channels(), SAMPLE_BUFFER_SIZE));

    if (const char* err = scaler_->Init(timeScale(stretch_),
                                        stretch_.sample_rate(),
                                        stretch_.channels(),
                                        pitchScale(stretch_),
                                        stretch_.bands(),
                                        stretch_.filter_overlap()))
      LOG(ERROR) << err;
  }

  void nextStretchedAudioBlock(const AudioSourceChannelInfo& info) {
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

  int64 processOneChunk(const AudioSourceChannelInfo& info) {
    int inSampleCount = scaler_->GetInputBufferSize(info.numSamples) / 2;
    buffer_->setSize(stretch_.channels(), inSampleCount, false, false, true);

    AudioSourceChannelInfo i;
    i.startSample = 0;
    i.numSamples = inSampleCount;
    i.buffer = buffer_.get();
    source()->getNextAudioBlock(i);

    for (int c = 0; c < stretch_.channels(); ++c)
      outOffset_[c] = info.buffer->getSampleData(c) + info.startSample;

    return scaler_->Process(buffer_->getArrayOfChannels(), &outOffset_.front(),
                            inSampleCount, info.numSamples);
  }

 private:
  ptr<AudioTimeScaler> scaler_;
  ptr<AudioSampleBuffer> buffer_;
};

}  // namespace

source::Stretchy* createAudioMagicStretchy(PositionableAudioSource* p,
                                           const Stretch& s) {
  return new AudioMagicStretchy(p, s);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

