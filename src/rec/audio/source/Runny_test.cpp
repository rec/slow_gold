#ifdef TODO

#include <gtest/gtest.h>

#include "rec/audio/source/TestSource_test.h"
#include "rec/audio/source/Runny.h"
#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {

namespace {

const int CHUNK_SIZE = 16;
const int BUFFER_SIZE = 64;

}

TEST(RecAudio, Runny1) {
  RunnyProto runnyProto;

  runnyProto.set_chunk_size(CHUNK_SIZE);
  runnyProto.set_buffer_size(BUFFER_SIZE);

  Runny runny(new Testy, runnyProto);
  runny.fillOnce();

  testSource(&runny);
}

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif
