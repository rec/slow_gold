#include <gtest/gtest.h>

#include "rec/audio/source/TestSource_test.h"
#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {

const int CHANNELS = 2;
const int FULL_BUFFER_SIZE = 128;

const int READ_OFFSET = 16;
const int WRITE_OFFSET = 64;

void testSource(int numSamples, PositionableAudioSource* source) {
  AudioSampleBuffer buffer(CHANNELS, FULL_BUFFER_SIZE);

  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  info.numSamples = numSamples;
  info.startSample = WRITE_OFFSET;

  source->setNextReadPosition(READ_OFFSET);
  source->getNextAudioBlock(info);

  for (int c = 0; c < CHANNELS; ++c) {
    for (int i = 0; i < numSamples; ++i) {
      EXPECT_EQ(Testy::getSample(READ_OFFSET + i),
                *buffer.getSampleData(c, WRITE_OFFSET + i))
        << "channel: " << c
        << ", sample: " << i
        << ", numSamples: " << numSamples;
    }
  }
}


}  // namespace source
}  // namespace audio
}  // namespace rec
