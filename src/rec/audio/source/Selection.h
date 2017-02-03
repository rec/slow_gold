#pragma once

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

    virtual void setSelection(const SampleRangeVector& s) {
        Lock l(lock_);
        selection_ = s;
    }

    const SampleRangeVector selection() const {
        Lock l(lock_);
        return selection_;
    }

    virtual int64 getTotalLength() const;
    virtual int64 getCorrectTotalLength() const;

  private:
    SampleRangeVector selection_;

    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Selection);
};

}  // namespace source
}  // namespace audio
}  // namespace rec
