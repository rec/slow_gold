#include <stdio.h>

#include <gtest/gtest.h>

#include "rec/util/TestData.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/audio/util/AudioFormatManager.h"

using namespace juce;

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

TEST(CreateReader, Create) {
  initializeOnce();
  AudioFormatReader *r = getAudioFormatManager()->createReaderFor(
      rec::util::testFile("test1.mp3"));

  ASSERT_FALSE(!r);
  StringPairArray& data = r->metadataValues;

  EXPECT_EQ(data["idversion"], "id3v2");
  EXPECT_EQ(data["TENC"], "Amadeus Pro");
  EXPECT_EQ(data["TIT2"], "The Title");
  EXPECT_EQ(data["TALB"], "The Album");
  EXPECT_EQ(data["TPE1"], "The Artist");
  EXPECT_EQ(data["TYER"], "2010");
  EXPECT_EQ(data["TRCK"], "2");
  EXPECT_EQ(data["TCON"], "Space punk");
  EXPECT_EQ(data["COMM"], "This is a comment.");

  delete r;
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
