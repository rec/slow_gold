#include "rec/audio/format/raw/RawFormat.h"
#include "rec/audio/format/raw/RawFormatReader.h"
#include "rec/audio/format/raw/RawFormatWriter.h"
#include "rec/base/Arraysize.h"

namespace rec {
namespace audio {
namespace format {
namespace raw {

RawFormat::RawFormat() : AudioFormat("raw", StringArray(".raw")) {}

AudioFormatReader* RawFormat::createReaderFor(InputStream* source, bool) {
    return new RawFormatReader(source);
}

AudioFormatWriter* RawFormat::createWriterFor(OutputStream* output,
                                              double sampleRateToUse,
                                              unsigned int numChannels,
                                              int bitsPerSample,
                                              const StringPairArray& /* meta */,
                                              int /* quality */) {
    return new RawFormatWriter(output, "raw", sampleRateToUse, numChannels,
                                                          bitsPerSample);
}

juce::Array<int> RawFormat::getPossibleSampleRates() {
    static int rates[] = {22050, 24000, 44100, 48000, 88200, 96000};
    return juce::Array<int>(rates, arraysize(rates));
}

juce::Array<int> RawFormat::getPossibleBitDepths() {
    static const int depths[] = {8, 16, 32};
    return juce::Array<int>(depths, arraysize(depths));
}

}  // namespace raw
}  // namespace format
}  // namespace audio
}  // namespace rec
