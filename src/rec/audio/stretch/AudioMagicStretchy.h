#ifndef __REC_AUDIO_STRETCH_AUDIOMAGICSTRETCHY__
#define __REC_AUDIO_STRETCH_AUDIOMAGICSTRETCHY__

#include "rec/audio/stretch/Stretcher.h"

class AudioTimeScaler;

namespace rec {
namespace audio {
namespace stretch {

class AudioMagicStretchy : public Stretcher {
 public:
  static const int SAMPLE_BUFFER_SIZE = 1000;

  AudioMagicStretchy(PositionableAudioSource* source, const Stretch& stretch);

 protected:
  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo& info);

 private:
  int64 processOneChunk(const AudioSourceChannelInfo& info);

  std::vector<float*> outOffset_;
  int channels_;

  ptr<AudioTimeScaler> scaler_;
  ptr<AudioSampleBuffer> buffer_;
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_AUDIOMAGICSTRETCHY__
