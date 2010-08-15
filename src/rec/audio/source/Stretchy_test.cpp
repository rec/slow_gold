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

  AudioSampleBuffer buffer(2, stretchy.getTotalLength());

  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  info.numSamples = stretchy.getTotalLength();
  info.startSample = 0;

  stretchy.getNextAudioBlock(info);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
