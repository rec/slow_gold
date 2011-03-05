#include <gtest/gtest.h>

#include "rec/audio/source/Testy.h"
#include "rec/audio/source/Runny.h"

namespace rec {
namespace audio {
namespace source {

namespace {

const int READ_OFFSET = 16;
const int WRITE_OFFSET = 64;
const int NUM_SAMPLES = 32;
const int BUFFER_SIZE = 128;
const int CHUNK_SIZE = 16;
const int CHANNELS = 2;

void runTest(int numSamples) {
  AudioSampleBuffer buffer(CHANNELS, BUFFER_SIZE);

  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  info.numSamples = numSamples;
  info.startSample = WRITE_OFFSET;

  RunnyProto runnyProto;
  runnyProto.set_chunk_size(CHUNK_SIZE);
  Runny runny(new Testy, runnyProto);
  runny.fillOnce();
  runny.fillOnce();

  runny.setNextReadPosition(READ_OFFSET);
  runny.getNextAudioBlock(info);

  for (int c = 0; c < CHANNELS; ++c) {
    for (int i = 0; i < numSamples; ++i) {
      EXPECT_EQ(Testy::getSample(READ_OFFSET + i),
                *buffer.getSampleData(c, WRITE_OFFSET + i))
        << "channel: " << c
        << ", sample: " << i
        << ", numSamples: " << numSamples
;
    }
  }
}

}

TEST(RecAudio, Runny) {
  runTest(NUM_SAMPLES);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
