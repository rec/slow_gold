#include <gtest/gtest.h>

#include "rec/audio/util/ConvertSample.h"

namespace rec {
namespace audio {

TEST(Audio, Convert) {
  for (int i = -32768; i <= 32767; ++i) {
    short s = i, s2;
    float f;
    convertSample(s, &f);
    convertSample(f, &s2);

    EXPECT_EQ(s, s2) << i << ", " << s << ", " << s2;
  }
}

}  // namespace audio
}  // namespace rec
