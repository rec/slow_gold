#ifndef __REC_AUDIO_FORMAT_MPG123_READER__
#define __REC_AUDIO_FORMAT_MPG123_READER__

#include <stdlib.h>
#include <sys/types.h>

#include "rec/audio/format/mpg123/Copier.h"
#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/audio/format/mpg123/CreateReader.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

class Reader : public juce::AudioFormatReader {
 public:
  ~Reader();

  virtual bool readSamples(int** destSamples,
                           int numDestChannels,
                           int startOffsetInDestBuffer,
                           int64 startSampleInFile,
                           int numSamples);

 private:
  Reader(juce::InputStream* in, const String& name, mpg123_handle* mh, Copier copier);

  friend Error createReader(juce::InputStream*,
                            juce::AudioFormatReader**, OutputFormat*, OutputFormat*);

  mpg123_handle* mh_;
  void* buffer_;
  size_t size_, allocated_;
  Copier copier_;


  DISALLOW_COPY_AND_ASSIGN(Reader);
};

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_FORMAT_MPG123_READER__
