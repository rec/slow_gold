#ifndef __REC_AUDIO_SOURCE_SELECTION__
#define __REC_AUDIO_SOURCE_SELECTION__

#include "rec/audio/source/Wrappy.h"
#include "rec/util/block/Block.h"

namespace rec {
namespace audio {
namespace source {

class Selection : public Wrappy {
 public:
  Selection(PositionableAudioSource* source) : Wrappy(source) {}

  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

  virtual bool isLooping() const { return true; }
  virtual void setLooping(bool looping) { DCHECK(looping); }

  void setSelection(const block::BlockSet& s);

 private:
  CriticalSection lock_;
  block::BlockSet selection_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Selection);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_SELECTION__
