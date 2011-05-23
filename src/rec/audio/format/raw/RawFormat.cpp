#include "rec/audio/format/raw/RawFormat.h"
#include "rec/base/Arraysize.h"

namespace rec {
namespace audio {
namespace format {
namespace raw {

RawFormat::RawFormat() : AudioFormat("raw", StringArray(".raw")) {}

AudioFormatReader* RawFormat::createReaderFor(InputStream* source,
                                              bool deleteStreamOnFail) {
  return NULL;
}

AudioFormatWriter* RawFormat::createWriterFor(OutputStream* output,
                                              double sampleRateToUse,
                                              unsigned int numChannels,
                                              int bitsPerSample,
                                              const StringPairArray& meta,
                                              int quality) {
  return NULL;
}

const juce::Array<int> RawFormat::getPossibleSampleRates() {
  static int rates[] = {22050, 24000, 44100, 48000, 88200, 96000};
  return juce::Array<int>(rates, arraysize(rates));
}

const juce::Array<int> RawFormat::getPossibleBitDepths() {
  static const int depths[] = {8, 16, 32, 64};
  return juce::Array<int>(depths, arraysize(depths));
}

}  // namespace raw
}  // namespace format
}  // namespace audio
}  // namespace rec
