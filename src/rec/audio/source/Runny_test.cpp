#include <gtest/gtest.h>

#include "rec/audio/source/Testy.h"
#include "rec/audio/source/Runny.h"

namespace rec {
namespace audio {
namespace source {

TEST(RecAudio, Runny) {
  static const int READ_OFFSET = 16;
  static const int WRITE_OFFSET = 64;

  AudioSampleBuffer buffer(2, 128);

  AudioSourceChannelInfo info;
  info.buffer = &buffer;
  info.numSamples = 32;
  info.startSample = WRITE_OFFSET;

  RunnyProto runnyProto;
  // runnyProto.set_chunk_size(16);
  Runny runny(new Testy, runnyProto);
  runny.fillOnce();

  runny.setNextReadPosition(READ_OFFSET);
  runny.getNextAudioBlock(info);

  for (int c = 0; c < 2; ++c) {
    for (int i = 0; i < 32; ++i) {
      EXPECT_EQ(Testy::getSample(READ_OFFSET + i),
                *buffer.getSampleData(c, WRITE_OFFSET + i));
    }
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
