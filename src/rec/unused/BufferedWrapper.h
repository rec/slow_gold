#ifndef __REC_SCALABLE_AUDIO_SOURCE
#define __REC_SCALABLE_AUDIO_SOURCE

#include "rec/audio/source/Buffered.h"
#include "rec/audio/stretch/TimeScaler.h"

namespace rec {
namespace audio {
namespace source {

class BufferedWrapper : public Buffered {
 public:
  virtual void fillOneBuffer(AudioSampleBuffer *toFill) = 0;

  BufferedWrapper(const String& name, const BufferDescription& desc)
      : Buffered(name, desc),
        source_(NULL) {
  }

  void prepareToPlay(int samplesPerBlockExpected,
                                          double sampleRate) {
    if (source_)
      source_->prepareToPlay(samplesPerBlockExpected, sampleRate);
  }

  void releaseResources() {
    if (source_)
      source_->releaseResources();
  }

  void setSource(AudioSource* source) {
    source_ = source;
    init();
  }

 protected:
  AudioSource* source_;

  DISALLOW_COPY_AND_ASSIGN(BufferedWrapper);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_SCALABLE_AUDIO_SOURCE
