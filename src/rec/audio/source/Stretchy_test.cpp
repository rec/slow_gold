#include <gtest/gtest.h>

#include "rec/audio/source/Stretchy.h"
#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {

TEST(RecAudioSource, Stretchy) {
  Testy testy;
  Stretchy stretchy(rec::audio::timescaler::TimeStretch(), &testy);
  Testy::expectNear(&stretchy, 0.0086, 2);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
