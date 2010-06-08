#include <stdio.h>

#include <gtest/gtest.h>

#include "juce_amalgamated.h"
#include "rec/audio/format/mpg123/CreateReader.h"
#include "rec/audio/format/mpg123/Mpg123.h"

#include "rec/audio/format/mpg123/TestReader.h"

using rec::audio::format::mpg123::Format;

TEST(Reader, All) {
  AudioFormatReader *reader = createTestReader();

}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
