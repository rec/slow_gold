#ifndef __REC_AUDIO_STRETCH_SOUNDTOUCH__
#define __REC_AUDIO_STRETCH_SOUNDTOUCH__

#include "rec/audio/stretch/Implementation.h"
#include "rec/audio/util/Frame.h"

namespace soundtouch { class SoundTouch; }

namespace rec {
namespace audio {
namespace stretch {

class SoundTouch : public Implementation {
 public:
  static const int INPUT_BUFFER_SAMPLES = 4096;

  SoundTouch(PositionableAudioSource* s, const Stretch& stretch);
  virtual ~SoundTouch();

  virtual void setStretch(const Stretch&);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

 private:
  bool fillInput(int numSamples);
  void putSamples(const AudioSourceChannelInfo& info);
  void copyToOutput(const AudioSourceChannelInfo& info);

 private:
  CriticalSection lock_;
  Frames<FloatFrame> frames_;

  ptr<soundtouch::SoundTouch> soundTouch_;
  AudioSampleBuffer buffer_;

  AudioSourceChannelInfo fetchInfo_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SoundTouch);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_SOUNDTOUCH__
