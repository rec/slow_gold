#include <stdio.h>

#include <gtest/gtest.h>

#include "juce_amalgamated.h"
#include "rec/audio/format/mpg123/CreateReader.h"
#include "rec/audio/format/mpg123/Mpg123.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

static const char* FILENAME = "../data/sin-stereo-64-tags-324-mono.mp3";

TEST(Reader, Create) {
  File file(FILENAME);
  ASSERT_TRUE(file.exists()) << file2 << " does not exist.";

  AudioFormatReader* reader = NULL;
  ASSERT_TRUE(!createReader(file.createInputStream(), &reader));
  ASSERT_FALSE(!reader);

  delete reader;
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
