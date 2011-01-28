#ifndef __REC_AUDIO_SOURCE_RUNNY__
#define __REC_AUDIO_SOURCE_RUNNY__

#include "rec/base/base.h"

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/util/Circular.h"

namespace rec {
namespace audio {
namespace source {

class Runny : public Thread, public Wrappy {
 public:
  Runny(PositionableAudioSource* source,
        const RunnyProto& d = RunnyProto::default_instance());

  virtual ~Runny();

  virtual void setNextReadPosition(int64 p);
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);

  // Try to pre-fill the lookahead buffer one slot.
  void fillOnce();

  void fill();

  virtual void run();

  bool isFull() const { return !filled_.remaining(); }

  util::Circular getFilled() const { return filled_; }

 private:
  AudioSampleBuffer buffer_;
  util::Circular filled_;
  const RunnyProto desc_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Runny);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_RUNNY__
