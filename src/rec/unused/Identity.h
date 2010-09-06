#ifndef __REC_IDENTITY_AUDIO_SOURCE
#define __REC_IDENTITY_AUDIO_SOURCE

#include "rec/audio/source/BufferedWrapper.h"

namespace rec {
namespace audio {
namespace source {

class Identity : public BufferedWrapper {
 public:
  Identity(const BufferDescription& d)
      : BufferedWrapper("Identity", d) {
  }

  virtual void fillOneBuffer(AudioSampleBuffer *toFill) {
    AudioSourceChannelInfo info;
    info.startSample = 0;
    info.numSamples = desc_.samples;
    info.buffer = toFill;
    source_->getNextAudioBlock(info);
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(Identity);
};

}  // namespace source
}  // namespace audio
}  // namespace rec



#endif  // __REC_IDENTITY_AUDIO_SOURCE
