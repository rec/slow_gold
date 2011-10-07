#include "rec/audio/source/AudioMagicStretchy.h"
#include "rec/audio/ammf_scaler/AudioTimeScaler.h"

namespace rec {
namespace audio {
namespace source {

namespace {

class AudioMagicStretchy : public Stretchy {
 public:
  AudioMagicStretchy(PositionableAudioSource* s)
      : Stretchy(s), scaler_(new AudioTimeScaler) {
  }

  void initializeStretcher() {
    scaler_.reset(new AudioTimeScaler);
    audio::stretch::Init(stretch_, scaler_.get());
  }

  int getInputSampleCount(int numSamples) const {
    return scaler_->GetInputBufferSize(numSamples) / 2;
  }

  int64 process(float** ins, int inSamples,
                          float** outs, int outSamples) {
    return scaler_->Process(ins, outs, inSamples, outSamples);
  }

 private:
  ptr<AudioTimeScaler> scaler_;
};

}  // namespace AudioMagicStretchy

Stretchy* createAudioMagicStretchy(PositionableAudioSource* p) {
  return new AudioMagicStretchy(p);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
