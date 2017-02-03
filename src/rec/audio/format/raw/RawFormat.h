#pragma once

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace format {
namespace raw {

class RawFormat : public juce::AudioFormat {
  public:
    RawFormat();
    virtual ~RawFormat() {}

    virtual AudioFormatReader* createReaderFor(InputStream* source,
                                               bool deleteStreamOnFail);

    virtual AudioFormatWriter* createWriterFor(OutputStream* output,
                                               double sampleRateToUse,
                                               unsigned int numChannels,
                                               int bitsPerSample,
                                               const StringPairArray& meta,
                                               int quality);

    virtual juce::Array<int> getPossibleSampleRates();
    virtual juce::Array<int> getPossibleBitDepths();

    virtual bool canDoStereo() { return true; }
    virtual bool canDoMono() { return true; }
    virtual bool isCompressed() { return false; }

  private:
    DISALLOW_COPY_ASSIGN_AND_LEAKS(RawFormat);
};

}  // namespace raw
}  // namespace format
}  // namespace audio
}  // namespace rec
