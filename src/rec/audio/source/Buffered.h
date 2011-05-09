#ifndef __REC_AUDIO_SOURCE_BUFFERED__
#define __REC_AUDIO_SOURCE_BUFFERED__

#include "rec/audio/Audio.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/Wrappy.h"
#include "rec/util/Circular.h"

namespace rec {
namespace audio {
namespace source {

// Buffered is a thread-based pre-fetching PositionableAudioSource wrapper.
class Buffered : public BufferSource {
 public:
  Buffered(PositionableAudioSource* source, SampleTime size);

  virtual ~Buffered() {}
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

  // Try to pre-fill the lookahead buffer one slot.
  void fillOnce(SampleTime chunkSize);

  bool isFull() const { ScopedLock l(lock_); return circular_.isFull(); }

 private:
  ptr<Source> source_;
  AudioSampleBuffer buffer_;
  Circular<SampleTime> circular_;
  CriticalSection lock_;
  bool prepared_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Buffered);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERED__
