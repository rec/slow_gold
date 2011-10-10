#include "rec/audio/stretch/AudioMagicStretchy.h"
#include "rec/audio/ammf_scaler/AudioTimeScaler.h"

namespace rec {
namespace audio {
namespace stretch {

namespace {

class AudioMagicStretchy : public source::Stretchy {
 public:
  AudioMagicStretchy(PositionableAudioSource* s, const Stretch& stretch)
      : Stretchy(s, stretch), scaler_(new AudioTimeScaler) {
  }

  void initializeStretcher() {
    scaler_.reset(new AudioTimeScaler);

    if (const char* err = scaler_->Init(timeScale(stretch_),
                                        stretch_.sample_rate(),
                                        stretch_.channels(),
                                        pitchScale(stretch_),
                                        stretch_.bands(),
                                        stretch_.filter_overlap()))
      LOG(ERROR) << err;
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

}  // namespace

source::Stretchy* createAudioMagicStretchy(PositionableAudioSource* p,
                                           const Stretch& s) {
  return new AudioMagicStretchy(p, s);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

