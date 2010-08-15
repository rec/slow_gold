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

}

}  // namespace source
}  // namespace audio
}  // namespace rec
