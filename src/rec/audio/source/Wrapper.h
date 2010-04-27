#ifndef __REC_AUDIO_SOURCE_WRAPPER_H__
#define __REC_AUDIO_SOURCE_WRAPPER_H__

#include "rec/audio/source/Buffered.h"
#include "rec/ammf_scaler/AudioTimeScaler.h"
#include "rec/audio/TimeScaler.h"

namespace rec {
namespace audio {
namespace source {

template <typename Base>
class Wrapper : public Base {
 public:
  template <typename String, typename Description>
  Wrapper(const String& name, const Description& desc)
      : Base(name, desc),
        source_(NULL) {
  }

  virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    if (source_)
      source_->prepareToPlay(samplesPerBlockExpected, sampleRate);
  }

  virtual void releaseResources() {
    if (source_)
      source_->releaseResources();
  }

  virtual void setSource(AudioSource* source) {
    source_ = source;
  }

 protected:
  AudioSource* source_;

  DISALLOW_COPY_AND_ASSIGN(Wrapper);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPER_H__
