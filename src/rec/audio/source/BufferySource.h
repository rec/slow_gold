#ifndef __REC_AUDIO_SOURCE_BUFFERYSOURCE__
#define __REC_AUDIO_SOURCE_BUFFERYSOURCE__

#include "rec/audio/CopySamples.h"

namespace rec {
namespace audio {
namespace source {

class BufferySource : public PositionableAudioSource {
 public:
  BufferySource(const AudioSampleBuffer& buffer) : buffer_(buffer) { }

  virtual void prepareToPlay(int, double) {}
  virtual void releaseResources() {}

  virtual void getNextAudioBlock (const AudioSourceChannelInfo& info) {
    audio::copyCircularSamples(buffer_, position_, info);
    setNextReadPosition((position_ + info.numSamples) % getTotalLength());
  }

  virtual void setNextReadPosition (int p) { position_ = p; }
  virtual int getNextReadPosition() const { return position_; };
  virtual int getTotalLength() const { return buffer_.getNumSamples();  }
  virtual bool isLooping() const { return looping_; }
  virtual void setLooping (bool shouldLoop) { looping_ = shouldLoop; }

 private:
  const AudioSampleBuffer& buffer_;
  bool looping_;
  int position_;
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERYSOURCE__
