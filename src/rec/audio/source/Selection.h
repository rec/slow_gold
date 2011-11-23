#ifndef __REC_AUDIO_SOURCE_SELECTION__
#define __REC_AUDIO_SOURCE_SELECTION__

#include "rec/base/RealTime.h"
#include "rec/audio/source/Wrappy.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/DataListener.h"
#include "rec/util/block/Block.h"

namespace rec {
namespace audio {
namespace source {

class Selection : public Wrappy, public DataListener<LoopPointList> {
 public:
  Selection(PositionableAudioSource* source) : Wrappy(source) {}

  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

  virtual bool isLooping() const { return true; }
  virtual void setLooping(bool looping) { DCHECK(looping); }

  virtual void onDataChange(const LoopPointList&);

  const block::BlockSet selection() const {
    Lock l(Wrappy::lock_);
    return selection_;
  }

  // Move the clock backward, taking into account the segments.
  void moveBackward(Samples<44100> dt);

 private:
  block::BlockSet selection_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Selection);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_SELECTION__
