#ifndef __REC_AUDIO_STRETCH_AUDIOMAGICSTRETCHY__
#define __REC_AUDIO_STRETCH_AUDIOMAGICSTRETCHY__

#include "rec/audio/stretch/Stretchy.h"

class AudioTimeScaler;

namespace rec {
namespace audio {
namespace stretch {

class AudioMagicStretchy : public Stretchy {
 public:
  static const int SAMPLE_BUFFER_SIZE = 1000;

  AudioMagicStretchy(PositionableAudioSource* s, const Stretch& stretch);

 protected:
  virtual void initializeStretcher(const Stretch& stretch);
  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo& info);

 private:
  int64 processOneChunk(const AudioSourceChannelInfo& info);

  std::vector<float*> outOffset_;
  int channels_;

  ptr<AudioTimeScaler> scaler_;
  ptr<AudioSampleBuffer> buffer_;
};

Stretchy* createAudioMagicStretchy(
    Source* p, const Stretch& s = Stretch::default_instance());

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_AUDIOMAGICSTRETCHY__
