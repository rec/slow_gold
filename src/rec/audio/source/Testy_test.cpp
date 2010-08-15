#include <gtest/gtest.h>
#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {

TEST(RecAudio, Testy) {
  AudioSampleBuffer buffer(2, 128);

  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  static const int SAMPLES = 32;
  static const int START = 64;
  static const int POSITION = 16;

  info.numSamples = SAMPLES;
  info.startSample = START;

  Testy testy;
  testy.setNextReadPosition(POSITION);
  testy.getNextAudioBlock(info);

  for (int c = 0; c < 2; ++c) {
    for (int i = 0; i < SAMPLES; ++i) {
      float sample = *info.buffer->getSampleData(c, START + i);
      EXPECT_EQ(sample, Testy::getSample(POSITION + i));
    }
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
