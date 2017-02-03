#include "rec/audio/format/mpg123/Format.h"

using namespace juce;

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

Format::Format() : AudioFormat(getTranslatedName(), getMp3FileExtensions()) {}

Format::~Format() {}

AudioFormatReader* Format::createReaderFor(InputStream* sourceStream,
                                           bool deleteStreamIfOpeningFails) {
    AudioFormatReader* reader = nullptr;
    if (auto e = createReader(sourceStream, &reader)) {
        std::cerr << "mpg123 create error:" << mpg123_plain_strerror(e) << "\n";
        if (deleteStreamIfOpeningFails)
            delete sourceStream;
    }

    return reader;
}

Array<int> Format::getPossibleSampleRates() {
    return getSampleRates();
}

Array<int> Format::getPossibleBitDepths() {
    return getBitDepths();
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
