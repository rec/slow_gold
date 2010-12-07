#include <gtest/gtest.h>

#include "rec/audio/source/Buffery.h"
#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {

TEST(RecAudio, Buffery) {
  Buffery bp(new Testy);
  bp.initialize();
  bp.resetFrom(2, 0);

  EXPECT_EQ(bp.available(), 0);
  EXPECT_EQ(bp.getNextReadPosition(), 0);
  EXPECT_TRUE(bp.fillNext(32));
  EXPECT_EQ(bp.available(), 32);

  bp.setNextReadPosition(31);
  EXPECT_EQ(bp.available(), 1);

  bp.setNextReadPosition(32);
  EXPECT_EQ(bp.available(), 0);

  bp.resetFrom(2, 108);
  EXPECT_EQ(bp.available(), 0);

  EXPECT_TRUE(bp.fillNext(32));
  EXPECT_EQ(bp.available(), 20);  // wrap-around...

  EXPECT_TRUE(bp.fillNext(12));
  EXPECT_EQ(bp.available(), 32);

  AudioSampleBuffer buffer(2, 32);
  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  info.numSamples = 24;
  info.startSample = 8;
  bp.getNextAudioBlock(info);

  for (int c = 0; c < 2; ++c) {
    for (int i = 0; i < info.numSamples; ++i)
      EXPECT_EQ(Testy::getSample(108 + i),
                *buffer.getSampleData(c, 8 + i));
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
