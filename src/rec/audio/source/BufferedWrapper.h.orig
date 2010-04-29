#ifndef __REC_SCALABLE_AUDIO_SOURCE
#define __REC_SCALABLE_AUDIO_SOURCE

#include "rec/audio/source/Buffered.h"
#include "rec/audio/source/Wrapper.h"
#include "rec/ammf_scaler/AudioTimeScaler.h"
#include "rec/audio/TimeScaler.h"

namespace rec {
namespace audio {
namespace source {

class BufferedWrapper : public Wrapper<Buffered> {
 public:
  virtual void fillOneBuffer(AudioSampleBuffer *toFill) = 0;

  BufferedWrapper(const String& name, const BufferDescription& desc)
      : Wrapper<Buffered>(name, desc) {
  }

  virtual void setSource(AudioSource* source) {
    Wrapper<Buffered>::setSource(source);
    Buffered::init();
  }

 protected:
  DISALLOW_COPY_AND_ASSIGN(BufferedWrapper);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_SCALABLE_AUDIO_SOURCE
