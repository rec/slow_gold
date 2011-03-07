#include <gtest/gtest.h>

#include "rec/audio/source/TestSource.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {

void runTest(int numSamples, int chunkSize, int bufferSize) {
  RunnyProto runnyProto;
  runnyProto.set_chunk_size(chunkSize);
  runnyProto.set_chunk_size(bufferSize);

  Runny runny(new Testy, runnyProto);
  runny.fillOnce();
  runny.fillOnce();
  testSource(numSamples, &runny);
}

TEST(RecAudio, Runny1) {
  runTest(32, 16, 24);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
