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
  // The source must already have been prepared.
  Buffered(Source* source, SampleTime size);

  virtual ~Buffered() {}
  virtual void getNextAudioBlock(const Info& info);

  // Try to pre-fill the lookahead buffer one slot.
  // Return true if some new bytes were filled, false if the buffer was full.
  bool fillBuffer(SampleTime chunkSize);

  void setNotifyThread(Thread* t) { notifyThread_ = t; }
  void notify() { if (notifyThread_) notifyThread_->notify(); }
  void setSource(Source* source, SampleTime offset);

 private:
  ptr<Source> source_;
  Buffer buffer_;
  Circular<SampleTime> circular_;
  CriticalSection lock_;
  Thread* notifyThread_;

  ptr<Source> nextSource_;
  SampleTime nextEnd_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Buffered);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_BUFFERED__
