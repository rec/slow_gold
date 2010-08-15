#include <gtest/gtest.h>

#include "rec/audio/source/Stretchy.h"
#include "rec/audio/source/Stretchy.cpp"
#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {

TEST(RecAudioSource, Stretchy) {
  Testy testy;
  Stretchy<Testy> stretchy(rec::audio::timescaler::Description(), &testy);

  AudioSourceChannelInfo info;
  info.numSamples = stretchy.getTotalLength();
  info.startSample = 0;

  AudioSampleBuffer buffer(2, info.numSamples);
  info.buffer = &buffer;

  stretchy.getNextAudioBlock(info);
  for (int i = 0; i < info.numSamples; ++i)
    EXPECT_NEAR(*buffer.getSampleData(0, i), Testy::getSample(i), 0.0086) << i;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
