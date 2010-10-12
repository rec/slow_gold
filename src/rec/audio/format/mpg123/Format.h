#ifndef __REC_AUDIO_FORMAT_MPG123_FORMAT__
#define __REC_AUDIO_FORMAT_MPG123_FORMAT__

#include "rec/audio/format/mpg123/Mpg123.h"
#include "rec/audio/format/mpg123/CreateReader.h"
#include "rec/audio/format/mpg123/NewHandle.h"

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

class Format : public juce::AudioFormat {
 public:
  Format();
  ~Format();

  virtual juce::AudioFormatReader* createReaderFor(juce::InputStream* source,
                                                   bool deleteStreamOnFail);

  virtual juce::AudioFormatWriter* createWriterFor(juce::OutputStream* output,
                                                   double sampleRateToUse,
                                                   unsigned int numChannels,
                                                   int bitsPerSample,
                                                   const StringPairArray& meta,
                                                   int quality) {
    return NULL;
  }

  virtual const juce::Array<int> getPossibleSampleRates();
  virtual const juce::Array<int> getPossibleBitDepths();

  virtual bool canDoStereo() { return true; }
  virtual bool canDoMono() { return true; }
  virtual bool isCompressed() { return true; }

  juce_UseDebuggingNewOperator

 private:
  DISALLOW_COPY_AND_ASSIGN(Format);
};

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec

#endif // __REC_AUDIO_FORMAT_MPG123_FORMAT__
