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
}

}  // namespace source
}  // namespace audio
}  // namespace rec
