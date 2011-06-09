#ifndef __REC_AUDIO_SOURCE_SEGGY__
#define __REC_AUDIO_SOURCE_SEGGY__

#include "rec/audio/source/Wrappy.h"
#include "rec/base/SamplePosition.h"
#include "rec/util/Range.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

class Seggy : public Wrappy {
 public:
  Seggy(const Range<SamplePosition>& r, PositionableAudioSource* s)
      : Wrappy(s), range_(r) {
    DCHECK(range_.size());
    position_ = -1;
    setNextReadPosition(0);
  }

  virtual int64 getTotalLength() const { return range_.size(); }

  virtual void setNextReadPosition(int64 p) {
    ScopedLock l(lock_);
    int64 newPosition = mod(juce::jmax(p, 0LL));
    if (newPosition != position_) {
      position_ = newPosition;
      source()->setNextReadPosition(position_ + range_.begin_);
    }
  }

 private:
  Range<SamplePosition> range_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Seggy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_SEGGY__
