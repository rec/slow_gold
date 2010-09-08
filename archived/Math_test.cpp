#include <gtest/gtest.h>
#include "rec/audio/Math.h"

namespace rec {
namespace audio {
namespace math {

TEST(RecAudio, Wraparound) {
  float samples[10];
  samples[0] = 0;
  samples[1] = 1;
  samples[2] = 2;

  wraparound(3, 7, samples);

  for (int i = 0; i < 10; ++i)
    EXPECT_EQ(samples[i], i % 3);
}

}  // namespace math
}  // namespace audio
}  // namespace rec
