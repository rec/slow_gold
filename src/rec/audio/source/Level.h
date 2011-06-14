#ifndef __REC_AUDIO_SOURCE_LEVEL__
#define __REC_AUDIO_SOURCE_LEVEL__

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/Audio.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace source {

class Level : public Wrappy,
              public Broadcaster<const LevelVector&> {
 public:
  explicit Level(Source* s = NULL) : Wrappy(s) {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i) {
    Wrappy::getNextAudioBlock(i);

    channels_ = i.buffer->getNumChannels();
    LevelVector result(channels_, 0.0);
    for (int c = 0; c < channels_; ++c)
      result[c] = getLevel(i, c);

    broadcast(result);
  }

  virtual float getLevel(const AudioSourceChannelInfo& info, int channel) {
    return info.buffer->getRMSLevel(channel, info.startSample, info.numSamples);
  }

  void clear() {
    broadcast(LevelVector(channels_, 0.0));
  }

 private:
  int channels_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Level);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_LEVEL__
