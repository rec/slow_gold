#ifndef __REC_AUDIO_SOURCE_TESTY__
#define __REC_AUDIO_SOURCE_TESTY__

#include <vector>
#include <glog/logging.h>
#include <gtest/gtest.h>

#include "rec/audio/source/Source.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

class Testy : public Source {
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

  static float expectNear(Source* s,
                          float delta,
                          int channels) {
    Testy t;
    return expectNear(s, &t, delta, channels);
  }

  static float expectNear(Source* s0,
                          Source* s1,
                          float delta,
                          int channels) {
    int length = std::min(s0->getTotalLength(), s1->getTotalLength());
    EXPECT_EQ(s0->getTotalLength(), s1->getTotalLength());

    float maxDelta = 0.0;

    scoped_ptr<AudioSampleBuffer> buffer[2];

    for (int i = 0; i < 2; ++i) {
      buffer[i].reset(new AudioSampleBuffer(channels, length));

      AudioSourceChannelInfo info;
      info.numSamples = length;
      info.startSample = 0;
      info.buffer = buffer[i].get();

      (i ? s1 : s0)->getNextAudioBlock(info);
    }

    for (int c = 0; c < channels; ++c) {
      for (int i = 0; i < length; ++i) {
        float samples[] = { *buffer[0]->getSampleData(c, i),
          *buffer[1]->getSampleData(c, i) };
        EXPECT_NEAR(samples[0], samples[1], delta)
        << "At sample " << i << " channel " << c;
        maxDelta = std::max(maxDelta, fabsf(samples[0] - samples[1]));
      }
    }

    EXPECT_LT(maxDelta, delta);
    return maxDelta;
  }
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_TESTY__
