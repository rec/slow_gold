#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/base/scoped_ptr.h"
#include "rec/util/Circular.h"
#include "rec/audio/source/Wrappy.h"

namespace rec {
namespace audio {
namespace source {

class Buffery : public Wrappy::Position {
 public:
  typedef rec::util::Circular Circular;

  Buffery(Source* source) : Wrappy::Position(source) {}

  // How many samples are available (already computed?)
  int64 available() const;

  // Is this buffer completely full?
  bool filled() const { return getTotalLength() <= available(); }

  bool ready(int size) const {
    return available() >= std::min(getTotalLength(), size);
  }

  // A change in the underlying source has invalidated the buffer, start
  // buffering again from this position.
  void resetFrom(int channels, int position);

  AudioSampleBuffer* buffer() { return buffer_.get(); }

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i);

  // Returns true if there is more to be filled.  Only call this from one
  // thread please, it's likely the underlying source is not thread-safe.
  bool fillNext(int64 chunkSize);

 private:
  Circular filled_;
  scoped_ptr<AudioSampleBuffer> buffer_;
  AudioSourceChannelInfo sourceInfo_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(Buffery);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
