#ifndef __REC_AUDIO_SOURCE_BUFFERYSOURCE__
#define __REC_AUDIO_SOURCE_BUFFERYSOURCE__

// This is a class backed by a fixed-size Buffer representing, for example, a
// track on disk or audio CD.

#include "rec/audio/Audio.h"
#include "rec/audio/util/CopySamples.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

class BufferSource : public PositionableAudioSource {
 public:
  explicit BufferSource(const Buffer& buffer);

  virtual void getNextAudioBlock(const Info& i);
  virtual void setNextReadPosition(int64 p);

  virtual int64 getNextReadPosition() const { return position_; };
  virtual int64 getTotalLength() const { return buffer_.getNumSamples();  }
  virtual bool isLooping() const { return looping_; }
  virtual void setLooping (bool shouldLoop) { looping_ = shouldLoop; }

  virtual void prepareToPlay(int s, double r) {}
  virtual void releaseResources() {}

 private:
  const Buffer& buffer_;
  int64 position_;
  bool looping_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(BufferSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERYSOURCE__
