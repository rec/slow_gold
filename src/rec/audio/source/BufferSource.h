#ifndef __REC_AUDIO_SOURCE_BUFFERYSOURCE__
#define __REC_AUDIO_SOURCE_BUFFERYSOURCE__

// This is a Source backed by a fixed-size Buffer representing, for example, a
// track on disk or audio CD.  The track wraps around the buffer automatically,
// resulting in perhaps very many copies of a very small track.

// It is up to the class controlling this class to make sure that the buffer is
// filled in time and that it is correctly locked.

#include "rec/audio/Audio.h"
#include "rec/audio/util/CopySamples.h"
#include "rec/audio/util/FillableBuffer.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {

namespace util { class FillableBuffer; }

namespace source {

class SourceWithPosition : public Source {
 public:
  virtual void getNextAudioBlock(const Info& i) = 0;
  virtual int64 getTotalLength() const = 0;

  virtual void setNextReadPosition(int64 p) {
    position_ = mod(p, std::max(1LL, getTotalLength()));
  }

  virtual int64 getNextReadPosition() const { return position_; };
  virtual bool isLooping() const { return looping_; }
  virtual void setLooping (bool shouldLoop) { looping_ = shouldLoop; }

  virtual void prepareToPlay(int s, double r) {}
  virtual void releaseResources() {}

 protected:
  int64 position_;
  bool looping_;
};

class BufferSource : public SourceWithPosition {
 public:
  BufferSource(const Buffer* b = NULL) : buffer_(b) {}
  BufferSource(const util::FillableBuffer& b) : buffer_(b.buffer_.get()) {}
  void setBuffer(const Buffer* b) { buffer_ = b; }

  virtual void getNextAudioBlock(const Info& i);
  virtual int64 getTotalLength() const { return buffer_->getNumSamples();  }

 private:
  const Buffer* buffer_;

  DISALLOW_COPY_AND_ASSIGN(BufferSource);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERYSOURCE__
