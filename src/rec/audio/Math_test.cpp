#include <gtest/gtest.h>
#include "rec/audio/Math.h"

namespace rec {
namespace audio {
namespace math {

TEST(RecAudio, RampWave) {
  EXPECT_FLOAT_EQ(rampWave(0, 100), 0.0);
  EXPECT_FLOAT_EQ(rampWave(1, 100), 0.01);
  EXPECT_FLOAT_EQ(rampWave(100, 100), 1.0);
  EXPECT_FLOAT_EQ(rampWave(101, 100), -1.0);
  EXPECT_FLOAT_EQ(rampWave(102, 100), -0.99);
  EXPECT_FLOAT_EQ(rampWave(201, 100), 0.0);
}

}  // namespace math
}  // namespace audio
}  // namespace rec
