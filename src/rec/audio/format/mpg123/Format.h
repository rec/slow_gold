#pragma once

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
    virtual ~Format();

    virtual juce::AudioFormatReader* createReaderFor(juce::InputStream* source,
                                                     bool deleteStreamOnFail);

    virtual juce::AudioFormatWriter* createWriterFor(
          juce::OutputStream* /* output */,
          double /* sampleRateToUse */,
          unsigned int /* numChannels */,
          int /* bitsPerSample */,
          const StringPairArray& /* meta */,
          int /* quality */) {
        return nullptr;
    }

    juce::Array<int> getPossibleSampleRates();
    juce::Array<int> getPossibleBitDepths();

    virtual bool canDoStereo() { return true; }
    virtual bool canDoMono() { return true; }
    virtual bool isCompressed() { return true; }

  private:
    DISALLOW_COPY_ASSIGN_AND_LEAKS(Format);
};

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
