#ifndef __REC_AUDIO_FORMAT_MPG123_TEST_READER__
#define __REC_AUDIO_FORMAT_MPG123_TEST_READER__

#include "juce_amalgamated.h"
#include "io/streams/juce_InputStream.h"
#include "audio/audio_file_formats/juce_AudioFormat.h"
#include "rec/audio/format/mpg123/CreateReader.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

inline AudioFormatReader* createTestReader() {
  static const char* FILENAME = "../../../data/test1.mp3";
  AudioFormatReader* reader = NULL;
  File file(FILENAME);
  if (file.exists()) {
    InputStream* in = FileInputSource(file).createInputStream();
    if (createReader(in, &reader)) {
      jassert(!reader);
    }
  }

  return reader;
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

#endif // __REC_AUDIO_FORMAT_MPG123_TEST_READER__
