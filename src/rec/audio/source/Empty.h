#ifndef __REC_AUDIO_SOURCE_EMPTY__
#define __REC_AUDIO_SOURCE_EMPTY__

#include "rec/audio/source/Clear.h"

namespace rec {
namespace audio {
namespace source {

class Empty : public PositionableAudioSource {
 public:
  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i) { clear(i); }
  virtual int64 getTotalLength() const { return 0; }
  virtual int64 getNextReadPosition() const { return 0; }
  virtual void setNextReadPosition(int64) {}

  virtual bool isLooping() const { return false; }
  virtual void setLooping(bool looping) {}

  virtual void prepareToPlay(int s, double r) {}
  virtual void releaseResources() {}
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_EMPTY__
