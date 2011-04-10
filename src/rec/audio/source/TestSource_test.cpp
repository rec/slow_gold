#include <gtest/gtest.h>

#include "rec/audio/source/TestSource_test.h"
#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {

const int CHANNELS = 2;
const int FULL_BUFFER_SIZE = 128;

// Make sure that a given PositionableAudioSource is the same as the test
// source.
void testSource(PositionableAudioSource* source,
                int numSamples,
                int readOffset,
                int writeOffset) {
  AudioSampleBuffer buffer(CHANNELS, FULL_BUFFER_SIZE);

  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  info.numSamples = numSamples;
  info.startSample = writeOffset;

  source->setNextReadPosition(readOffset);
  source->getNextAudioBlock(info);

  for (int c = 0; c < CHANNELS; ++c) {
    for (int i = 0; i < numSamples; ++i) {
      EXPECT_EQ(Testy::getSample(readOffset + i),
                *buffer.getSampleData(c, writeOffset + i))
        << "channel: " << c
        << ", sample: " << i
        << ", numSamples: " << numSamples;
    }
  }
}


}  // namespace source
}  // namespace audio
}  // namespace rec
