#include <gtest/gtest.h>
#include "rec/audio/Math.h"

namespace rec {
namespace audio {
namespace math {

TEST(RecAudio, RampWave) {
  EXPECT_EQ(rampWave(0, 100), 0.0);
}

}  // namespace math
}  // namespace audio
}  // namespace rec
