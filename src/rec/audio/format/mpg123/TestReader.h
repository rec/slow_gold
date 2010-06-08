#ifndef __REC_AUDIO_FORMAT_MPG123_TEST_READER__
#define __REC_AUDIO_FORMAT_MPG123_TEST_READER__

#include "juce_amalgamated.h"
#include "io/streams/juce_InputStream.h"
#include "audio/audio_file_formats/juce_AudioFormat.h"
#include "rec/audio/format/mpg123/CreateReader.h"
#include "rec/audio/format/mpg123/Format.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

static const char* FILENAME = "../../../data/test1.";

inline AudioFormatReader* createTestReader(const String& suffix) {
  File file(FILENAME + suffix);
  if (file.exists()) {
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
    formatManager.registerFormat(new Format(), false);
    return formatManager.createReaderFor(file);
  }

  return NULL;
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

#endif // __REC_AUDIO_FORMAT_MPG123_TEST_READER__
