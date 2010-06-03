#ifndef __REC_AUDIO_FORMAT_MPG123_CREATE_READER__
#define __REC_AUDIO_FORMAT_MPG123_CREATE_READER__

#include "juce_amalgamated.h"
#include "io/streams/juce_InputStream.h"
#include "audio/audio_file_formats/juce_AudioFormat.h"

#include "rec/audio/format/mpg123/Mpg123.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

// A prescan function is called after the mpg123_handle is created but before
// it scans the file.  Use this opportunity to do things like setting which
// format we accept.
typedef Error (*Prescan)(mpg123_handle* mh);

Error empty_prescan(mpg123_handle* mh);
Error int_32_44100_prescan(mpg123_handle* mh);

// Create a reader from an InputStream, or return an error.
Error createReader(InputStream* sourceStream,
                   AudioFormatReader** reader,
                   Prescan prescan = int_32_44100_prescan);

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

#endif // __REC_AUDIO_FORMAT_MPG123_CREATE_READER__
