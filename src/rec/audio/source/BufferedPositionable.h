#ifndef __REC_AUDIO_SOURCE_BUFFEREDPOSITIONABLE__
#define __REC_AUDIO_SOURCE_BUFFEREDPOSITIONABLE__

#include "rec/util/Circular.h"
#include "rec/audio/source/Wrappy.h"

namespace rec {
namespace audio {
namespace source {

template <typename Source>
class BufferedPositionable : public PositionWrappy<Source> {
 public:
  typedef rec::util::Circular Circular;

  BufferedPositionable(int channels, Source* source);

  virtual void setNextReadPosition(int position);

  // How many samples are available (already computed?)
  int64 available() const;

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

  DISALLOW_COPY_AND_ASSIGN(BufferedPositionable);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFEREDPOSITIONABLE__
