#ifndef __REC_AUDIO_SOURCE_LEVEL__
#define __REC_AUDIO_SOURCE_LEVEL__

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/Audio.h"
#include "rec/util/Listener.h"
#include "rec/util/StateListener.h"

namespace rec {
namespace audio {
namespace source {

class Level : public Wrappy {
 public:
  explicit Level(Source* s = nullptr) : Wrappy(s), channels_(2) {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i) {
    Wrappy::getNextAudioBlock(i);

    channels_ = i.buffer->getNumChannels();
    LevelVector result(channels_, 0.0);
    for (int c = 0; c < channels_; ++c)
      result[c] = getLevel(i, c);
    broadcastState<const LevelVector&>(result);
  }

  virtual float getLevel(const AudioSourceChannelInfo& info, int channel) {
    return info.buffer->getRMSLevel(channel, info.startSample, info.numSamples);
  }

  virtual std::pair<float, float> getMinMax(const AudioSourceChannelInfo& info,
                                            int channel) {
    auto r = info.buffer->findMinMax(channel, info.startSample, info.numSamples);
    return std::make_pair(r.getStart(), r.getEnd());
  }

  void clear() {
    broadcastState<const LevelVector&>(LevelVector(channels_, 0.0));
  }

 private:
  int channels_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Level);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_LEVEL__
