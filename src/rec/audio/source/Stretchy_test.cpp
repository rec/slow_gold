#include <gtest/gtest.h>

#include "rec/audio/source/Stretchy.h"
#include "rec/audio/source/Testy.h"
#include "rec/audio/stretch/Stretchy.pb.h"

namespace rec {
namespace audio {
namespace source {

TEST(RecAudioSource, Stretchy) {
  Stretchy stretchy(new Testy(), stretch::StretchyProto());

  Testy::expectNear(&stretchy, 0.0086, 2);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
