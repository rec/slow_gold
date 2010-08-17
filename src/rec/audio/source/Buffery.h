#ifndef __REC_AUDIO_SOURCE_BUFFERY__
#define __REC_AUDIO_SOURCE_BUFFERY__

#include "rec/util/Circular.h"
#include "rec/audio/source/Wrappy.h"

namespace rec {
namespace audio {
namespace source {

template <typename Source>
class Buffery : public PositionWrappy<Source> {
 public:
  typedef rec::util::Circular Circular;

  Buffery(int channels, Source* source);

  virtual void setNextReadPosition(int position);

  // How many samples are available (already computed?)
  int64 available() const;

  // Is this buffer completely full?
  bool filled() const { return this->getTotalLength() <= available(); }

  bool ready(int size) const {
    return (available() >= std::min(this->getTotalLength(), size));
  }

  AudioSampleBuffer* buffer() { return &buffer_; }

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i);

  // Returns true if there is more to be filled.  Only call this from one
  // thread please, it's likely the underlying source is not thread-safe.
  bool fillNext(int64 chunkSize);

 private:
  Circular filled_;
  AudioSampleBuffer buffer_;
  CriticalSection lock_;
  AudioSourceChannelInfo sourceInfo_;

  DISALLOW_COPY_AND_ASSIGN(Buffery);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#include "Buffery.cpp"

#endif  // __REC_AUDIO_SOURCE_BUFFERY__
