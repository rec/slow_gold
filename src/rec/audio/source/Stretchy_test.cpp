#include <gtest/gtest.h>

#include "rec/audio/source/Stretchy.h"
#include "rec/audio/source/Stretchy.cpp"
#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {


TEST(RecAudioSource, Stretchy) {
  Testy testy;
  Stretchy<Testy> stretchy(rec::audio::timescaler::Description(), &testy);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
