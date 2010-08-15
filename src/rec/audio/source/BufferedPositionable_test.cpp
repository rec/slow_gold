#include <gtest/gtest.h>
#include "rec/audio/source/BufferedPositionable.h"
#include "rec/audio/source/Testy.h"

#include "rec/audio/source/BufferedPositionable.cpp"

namespace rec {
namespace audio {
namespace source {

TEST(RecAudio, BufferedPositionable) {
  Testy testy;
  BufferedPositionable<Testy> bp(2, &testy);

  EXPECT_EQ(bp.available(), 0);
  EXPECT_EQ(bp.getNextReadPosition(), 0);
  EXPECT_TRUE(bp.fillNext(32));
  EXPECT_EQ(bp.available(), 32);

  bp.setNextReadPosition(31);
  EXPECT_EQ(bp.available(), 1);

  bp.setNextReadPosition(32);
  EXPECT_EQ(bp.available(), 0);

  bp.setNextReadPosition(108);
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
}

}  // namespace source
}  // namespace audio
}  // namespace rec
