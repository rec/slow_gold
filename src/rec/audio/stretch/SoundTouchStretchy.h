#ifndef __REC_AUDIO_STRETCH_SOUNDTOUCHSTRETCHY__
#define __REC_AUDIO_STRETCH_SOUNDTOUCHSTRETCHY__

#include "rec/audio/stretch/Stretchy.h"
#include "rec/audio/util/Frame.h"

namespace soundtouch { class SoundTouch; }

namespace rec {
namespace audio {
namespace stretch {

class SoundTouchStretchy : public Stretchy {
 public:
  static const int INPUT_BUFFER_SAMPLES = 4096;

  SoundTouchStretchy(PositionableAudioSource* s, const Stretch& stretch);
  virtual ~SoundTouchStretchy();

  virtual void initializeStretcher(const Stretch& stretch);

 protected:
  virtual void nextStretchedAudioBlock(const AudioSourceChannelInfo& info);

 private:
  bool fillInput(int numSamples);
  void putSamples(const AudioSourceChannelInfo& info);
  void copyToOutput(const AudioSourceChannelInfo& info);

 private:
  Frames<FloatFrame> frames_;

  ptr<soundtouch::SoundTouch> soundTouch_;
  AudioSampleBuffer buffer_;

  AudioSourceChannelInfo fetchInfo_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(SoundTouchStretchy);
};

Stretchy* createSoundTouchStretchy(Source* p, const Stretch& s);

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_SOUNDTOUCHSTRETCHY__
