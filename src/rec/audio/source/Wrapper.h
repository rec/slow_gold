#ifndef __REC_AUDIO_SOURCE_WRAPPER_H__
#define __REC_AUDIO_SOURCE_WRAPPER_H__

#include "rec/audio/source/Buffered.h"
#include "rec/audio/TimeScaler.h"

namespace rec {
namespace audio {
namespace source {

class Wrapper : public PositionableAudioSource {
 public:
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


template <typename Base>
class LoopWrapper : public Wrapper<Base> {


}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_WRAPPER_H__
