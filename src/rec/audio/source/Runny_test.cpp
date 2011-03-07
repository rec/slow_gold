#include <gtest/gtest.h>

#include "rec/audio/source/Testy.h"
#include "rec/audio/source/Runny.h"

namespace rec {
namespace audio {
namespace source {

namespace {

const int CHANNELS = 2;
const int FULL_BUFFER_SIZE = 128;

const int READ_OFFSET = 16;
const int WRITE_OFFSET = 64;

void runTest(int numSamples, Runny* runny) {
  AudioSampleBuffer buffer(CHANNELS, FULL_BUFFER_SIZE);

  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  info.numSamples = numSamples;
  info.startSample = WRITE_OFFSET;

  runny->setNextReadPosition(READ_OFFSET);
  runny->getNextAudioBlock(info);

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

void runTest(int numSamples, int chunkSize, int bufferSize) {
  RunnyProto runnyProto;
  runnyProto.set_chunk_size(chunkSize);
  runnyProto.set_chunk_size(bufferSize);

  Runny runny(new Testy, runnyProto);
  runny.fillOnce();
  runny.fillOnce();
  runTest(numSamples, &runny);
}

}

TEST(RecAudio, Runny1) {
  runTest(32, 16, 24);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
