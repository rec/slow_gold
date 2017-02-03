#include "rec/audio/util/BufferedReaderImpl.h"

#include "rec/audio/source/FrameSource.h"
#include "rec/audio/util/ConvertSample.h"
#include "rec/audio/util/Frame.h"
#include "rec/base/DropDead.h"
#include "rec/base/SampleTime.h"

namespace rec {
namespace audio {
namespace util {

template <typename Sample, int CHANNELS>
BufferedReaderImpl<Sample, CHANNELS>::BufferedReaderImpl(SampleTime s)
        : blockSize_(s), intBuffer_(s), floatBuffer_(s) {
    CHECK_DDD(194, 439, int64, int64);
}

template <typename Sample, int CHANNELS>
SampleTime BufferedReaderImpl<Sample, CHANNELS>::doFillNextBlock(
        const SampleRange& b) {
    Lock l(lock_);

    if (!reader_) {
        LOG(DFATAL) << "No reader!";
        return 0;
    }

    SampleTime size = std::min(b.size(), blockSize_);

    int32** pointers = reader_->usesFloatingPointData ?
        reinterpret_cast<int32**>(floatBuffer_.pointers_) : intBuffer_.pointers_;

    int readerChannels = reader_->numChannels;
    int channels = std::min(CHANNELS, readerChannels);
    if (!reader_->read(pointers, channels, b.begin_, size.toInt(), false)) {
        LOG(DFATAL) << "Reader failed to read!";
        return 0;
    }

    InterleavedFrame<Sample, CHANNELS>* frame = frames_.frames() +
        static_cast<int>(b.begin_);
    // I'm not sure why that cast is necessary...

    for (int i = 0; i < size; ++i, ++frame) {
        for (int c = 0; c < CHANNELS; ++c) {
            int cr = c % readerChannels;  // round-robin allocation.
            if (reader_->usesFloatingPointData) {
                float sample = floatBuffer_.pointers_[cr][i];
                convertSample<float, Sample>(sample, &frame->sample_[c]);
            } else {
                int32 sample = intBuffer_.pointers_[cr][i];
                convertSample<int32, Sample>(sample, &frame->sample_[c]);
            }
        }
    }

    return size;
}

template <typename Sample, int CHANNELS>
Source* BufferedReaderImpl<Sample, CHANNELS>::makeSource() const {
    return new source::FrameSource<Sample, CHANNELS>(frames_);
}

template <typename Sample, int CHANNELS>
bool BufferedReaderImpl<Sample, CHANNELS>::setLength(int64 length) {
    bool success = frames_.setLength(length);
    Fillable::setLength(success ? length : 0);
    return success;
}

template <typename Sample, int CHANNELS>
BufferedReader* makeBufferedReader(int size) {
    return new BufferedReaderImpl<Sample, CHANNELS>(size);
}

template BufferedReader* makeBufferedReader<short, 2>(int);

}  // namespace util
}  // namespace audio
}  // namespace rec

