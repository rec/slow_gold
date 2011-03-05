#include <gtest/gtest.h>

#include "rec/audio/source/Testy.h"
#include "rec/audio/source/Runny.h"

namespace rec {
namespace audio {
namespace source {

TEST(RecAudio, Runny) {
  AudioSampleBuffer buffer(2, 128);

  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  info.numSamples = 32;
  info.startSample = 64;

  RunnyProto runnyProto;
  Runny runny(new Testy, runnyProto);
  runny.fillOnce();

  static const int OFFSET = 16;
  runny.setNextReadPosition(OFFSET);
  runny.getNextAudioBlock(info);

  for (int c = 0; c < 2; ++c) {
    for (int i = 0; i < 32; ++i)
      EXPECT_EQ(Testy::getSample(OFFSET + i), *buffer.getSampleData(c, 64 + i));
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
