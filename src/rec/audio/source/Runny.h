#ifndef __REC_AUDIO_SOURCE_RUNNY__
#define __REC_AUDIO_SOURCE_RUNNY__

#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/ThreadedSource.h"
#include "rec/util/Circular.h"

namespace rec {
namespace audio {
namespace source {

// Runny is a thread-based pre-fetching PositionableAudioSource wrapper.
class Runny : public ThreadedSource {
 public:
  Runny(PositionableAudioSource* source,
        const RunnyProto& d = RunnyProto::default_instance());

  virtual ~Runny();

  virtual void setNextReadPosition(int64 p);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

  // Try to pre-fill the lookahead buffer one slot.
  void fillOnce();

  virtual void run();

  bool isFull() const { return filled_.isFull(); }

  Circular<SampleTime> getFilled() const { return filled_; }

 private:
  AudioSampleBuffer buffer_;
  Circular<SampleTime> filled_;
  const RunnyProto desc_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Runny);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_RUNNY__
