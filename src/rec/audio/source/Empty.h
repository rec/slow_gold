#ifndef __REC_AUDIO_SOURCE_EMPTY__
#define __REC_AUDIO_SOURCE_EMPTY__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

class Empty : public PositionableAudioSource {
 public:
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo&) {}
  virtual int getTotalLength() const { return 0; }
  virtual int getNextReadPosition() const { return 0; }
  virtual void setNextReadPosition(int) {}

  virtual bool isLooping() const { return false; }
  virtual void setLooping(bool looping) {}

  virtual void prepareToPlay(int s, double r) {}
  virtual void releaseResources() {}
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_EMPTY__
