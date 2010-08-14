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

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info) {
    for (int c = 0; c < info.buffer->getNumChannels(); ++c) {
      for (int i = 0; i < info.numSamples; ++i) {
        float samp = (position_ + i % SIZE) / (1.0 * SIZE);
        *info.buffer->getSampleData(c, i + info.startSample) = samp;
      }
    }
    position_ += info.numSamples;
  }

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
