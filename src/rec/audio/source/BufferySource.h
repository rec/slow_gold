#ifndef __REC_AUDIO_SOURCE_BUFFERYSOURCE__
#define __REC_AUDIO_SOURCE_BUFFERYSOURCE__

#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace audio {
namespace source {

class BufferySource : public PositionableAudioSource,
                      public listener::Broadcaster<int> {
 public:
  BufferySource(const AudioSampleBuffer& buffer) : buffer_(buffer) {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info) {
    copyCircularSamples(buffer_, position_, info);
    setNextReadPosition((position_ + info.numSamples) % getTotalLength());
  }

  virtual void setNextReadPosition(int newPosition) {
    position_ = position;
    broadcast(position_);
  }

  virtual int getNextReadPosition() const { return position_; };
  virtual int getTotalLength() const { return buffer_->getTotalLength(); }
  virtual bool isLooping() const { return looping_; }
  virtual void setLooping (bool shouldLoop) { looping_ = shouldLoop; }
  virtual void prepareToPlay(int, double) {}
  virtual void releaseResources() {}

 private:
  const AudioSampleBuffer& buffer_;
  bool looping_;
  int position_;
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERYSOURCE__
