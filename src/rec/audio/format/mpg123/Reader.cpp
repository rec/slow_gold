#include <stdlib.h>
#include <sys/types.h>

#include "rec/audio/format/mpg123/Reader.h"
#include "rec/audio/format/mpg123/NewHandle.h"
#include "rec/audio/format/mpg123/Format.h"

using namespace juce;

namespace rec {
namespace audio {
namespace format {
namespace mpg123 {

Reader::Reader(InputStream* in, const String& formatName, mpg123_handle* mh,
               Copier copier)
    : AudioFormatReader(in, formatName),
        mh_(mh),
        buffer_(nullptr),
        size_(0),
        allocated_(0),
        copier_(copier) {
}

Reader::~Reader() {
    mpg123_close(mh_);
    mpg123_delete(mh_);

    free(buffer_);
}

bool Reader::readSamples(int** dest, int destChannels, int destOffset,
                         int64 startSampleInFile, int numSamples) {
    if (mpg123_seek(mh_, static_cast<size_t>(startSampleInFile), SEEK_SET) < 0)
        return false;

    int64 bytesPerSample = this->bitsPerSample / 8;
    size_ = numSamples * numChannels * bytesPerSample;
    int intSize = static_cast<int>(size_);

    if (allocated_ < size_) {
        if (buffer_)
            free(buffer_);

        buffer_ = static_cast<uint8*>(malloc(intSize));
        allocated_ = size_;
    }

    size_t bytesCopied;
    Error e = mpg123_read(mh_, buffer_, intSize, &bytesCopied);
    if (e != MPG123_DONE && e != MPG123_OK)
        return false;

    int64 sourceSize = bytesCopied / (bytesPerSample * numChannels);
    copier_(dest, destChannels, destOffset, buffer_, numChannels, sourceSize);
    return (bytesCopied == size_);
}

}  // namespace mpg123
}  // namespace format
}  // namespace audio
}  // namespace rec
