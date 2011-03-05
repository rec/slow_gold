#include <gtest/gtest.h>

#include "rec/audio/source/Testy.h"
#include "rec/audio/source/Runny.h"

namespace rec {
namespace audio {
namespace source {

namespace {

const int CHANNELS = 2;
const int BUFFER_SIZE = 128;

const int READ_OFFSET = 16;
const int WRITE_OFFSET = 64;

void runTest(int numSamples, int chunkSize) {
  AudioSampleBuffer buffer(CHANNELS, BUFFER_SIZE);

  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  info.numSamples = numSamples;
  info.startSample = WRITE_OFFSET;

  RunnyProto runnyProto;
  runnyProto.set_chunk_size(chunkSize);
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
        << ", chunkSize: " << chunkSize;
    }
  }
}

}

TEST(RecAudio, Runny1) {
  runTest(32, 24);
}

TEST(RecAudio, Runny2) {
  runTest(32, 23);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
