#ifndef __REC_AUDIO_SOURCE_BUFFERYSOURCE__
#define __REC_AUDIO_SOURCE_BUFFERYSOURCE__

#include "rec/audio/CopySamples.h"
#include "rec/audio/source/Empty.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

class BufferSource : public Empty {
 public:
  explicit BufferSource(const AudioSampleBuffer& buffer)
      : buffer_(buffer), position_(0), looping_(true) {
  }

  virtual void getNextAudioBlock (const AudioSourceChannelInfo& i) {
    copyCircularSamples(buffer_, position_, i);
    setNextReadPosition(mod(position_ + i.numSamples, getTotalLength()));
  }

  virtual void setNextReadPosition(int p) {
    position_ = p;
  }
  virtual int getNextReadPosition() const { return position_; };
  virtual int getTotalLength() const { return buffer_.getNumSamples();  }
  virtual bool isLooping() const { return looping_; }
  virtual void setLooping (bool shouldLoop) { looping_ = shouldLoop; }

 private:
  const AudioSampleBuffer& buffer_;
  int position_;
  bool looping_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(BufferSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERYSOURCE__
