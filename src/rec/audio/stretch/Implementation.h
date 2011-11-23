#ifndef __REC_AUDIO_STRETCH_IMPLEMENTATION__
#define __REC_AUDIO_STRETCH_IMPLEMENTATION__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace stretch {

class Stretch;

class Implementation {
 public:
  static const int INITIAL_BUFFER_SIZE = (1 << 14);

  Implementation(PositionableAudioSource* s, int channels = 2);
  virtual ~Implementation() {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo&) = 0;
  virtual void setStretch(const Stretch&) = 0;

 protected:
  float** getSourceSamples(int);

 private:
  PositionableAudioSource* source_;
  AudioSampleBuffer buffer_;
  AudioSourceChannelInfo info_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Implementation);
};

}  // namespace stretch
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_STRETCH_IMPLEMENTATION__
