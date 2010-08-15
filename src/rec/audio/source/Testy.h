#ifndef __REC_AUDIO_SOURCE_TESTY__
#define __REC_AUDIO_SOURCE_TESTY__

#include <vector>
#include <glog/logging.h>

#include "juce_amalgamated.h"

namespace rec {
namespace audio {
namespace source {

class Testy : public PositionableAudioSource {
 public:
  static const int SIZE = 128;
  Testy() : position_(0) {}

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& i) {
    for (int c = 0; c < i.buffer->getNumChannels(); ++c) {
      for (int s = 0; s < i.numSamples; ++s)
        *i.buffer->getSampleData(c, s + i.startSample) = getSample(position_ + s);
    }
    position_ += i.numSamples;
  }

  static float getSample(int p) { return (p % SIZE) / (1.0 * SIZE); }

  virtual int getTotalLength() const { return SIZE; }

  virtual int getNextReadPosition() const { return position_; }
  virtual void setNextReadPosition(int p) { position_ = p; }

  virtual bool isLooping() const { return true; }
  virtual void setLooping(bool looping) {}
  virtual void prepareToPlay(int s, double r) {}
  virtual void releaseResources() {}

  int position_;
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_TESTY__
