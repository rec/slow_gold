#include "rec/audio/stretch/SoundTouchStretchy.h"

namespace rec {
namespace audio {
namespace stretch {

namespace {

class SoundTouchStretchy : public source::Stretchy {
 public:
  SoundTouchStretchy(PositionableAudioSource* s, const Stretch& stretch)
      : Stretchy(s, stretch) {
  }

  void initializeStretcher() {
  }

  int getInputSampleCount(int numSamples) const {
    return 0;
  }

  int64 process(float** ins, int inSamples,
                          float** outs, int outSamples) {
    return 0;
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(SoundTouchStretchy);
};

}  // namespace

source::Stretchy* createSoundTouchStretchy(PositionableAudioSource* p,
                                           const Stretch& s) {
  return new SoundTouchStretchy(p, s);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec

