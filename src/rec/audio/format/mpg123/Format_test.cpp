#include <gtest/gtest.h>

#include "juce_amalgamated.h"
#include "rec/audio/format/mpg123/Format.h"
#include "rec/audio/format/mpg123/Mpg123.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

static const char* FILENAME = "../../../data/sin-stereo-64-tags-324-mono.mp3";

TEST(Format, IntFormat) {
  File file(FILENAME);
  ASSERT_TRUE(file.exists());
  InputStream* in = FileInputSource(file).createInputStream();
  AudioFormatReader* reader = Format().createReaderFor(in, true);
  ASSERT_FALSE(!reader);
  delete reader;
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
