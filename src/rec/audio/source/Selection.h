#ifndef __REC_AUDIO_SOURCE_SELECTION__
#define __REC_AUDIO_SOURCE_SELECTION__

#include "rec/base/SampleTime.h"
#include "rec/audio/source/Wrappy.h"
#include "rec/util/LoopPoint.h"
#include "rec/data/DataListener.h"

namespace rec {
namespace audio {
namespace source {

class Selection : public Wrappy {
 public:
  Selection(PositionableAudioSource* source) : Wrappy(source) {}

  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo&);

  virtual bool isLooping() const { return true; }
  virtual void setLooping(bool looping) { DCHECK(looping); }

  virtual void setSelection(const SampleTimeVector& s) {
    Lock l(lock_);
    selection_ = s;
  }

  const SampleTimeVector selection() const {
    Lock l(lock_);
    return selection_;
  }

  virtual int64 getTotalLength() const;
  virtual int64 getCorrectTotalLength() const;

 private:
  SampleTimeVector selection_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Selection);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_SELECTION__
