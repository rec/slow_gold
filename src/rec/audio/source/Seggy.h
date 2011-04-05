#ifndef __REC_AUDIO_SOURCE_SEGGY__
#define __REC_AUDIO_SOURCE_SEGGY__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/Range.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace source {

class Seggy : public Wrappy {
 public:
  Seggy(const SampleRange& r, PositionableAudioSource* s)
      : Wrappy(s), range_(r) {
    DCHECK(range_.size());
  }

  virtual int64 getTotalLength() const { return range_.size(); }

  void setNextReadPosition(int64 p) {
    ScopedLock l(lock_);
    p = juce::jmax(p, 0LL);
    p = juce::jmin(p + range_.begin_, range_.end_) - range_.begin_;
    position_ = p;
    source()->setNextReadPosition(p + range_.begin_);
  }

virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
  setNextReadPosition(position_);
  Wrappy::getNextAudioBlock(info);
}

 private:
  SampleRange range_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Seggy);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_SEGGY__
