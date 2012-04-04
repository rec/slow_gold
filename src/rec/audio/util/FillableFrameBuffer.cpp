#include "rec/audio/util/FillableFrameBuffer.h"
#include "rec/audio/util/ConvertSample.h"

namespace rec {
namespace audio {
namespace util {

template <typename Sample, int CHANNELS>
FillableFrameBuffer<Sample, CHANNELS>::FillableFrameBuffer(int blockSize)
    : blockSize_(blockSize) {
  CHECK_DDD(194, 439, int64, int64);
  for (int i = 0; i < CHANNELS; ++i) {
    buffer_[i].resize(blockSize);
    bufferPointers_[i] = &buffer_[i][0];
  }
}

template <typename Sample, int CHANNELS>
Samples<44100> FillableFrameBuffer<Sample, CHANNELS>::setReader(
    AudioFormatReader* reader) {
  Lock l(lock_);
  if (!reader) {
    reader_.reset();
    return 0;
  }

  Samples<44100> size = reader->lengthInSamples;
  if (!frames_.setLength(size)) {
    LOG(ERROR) << "Ran out of memory, unable to set frame length";
    return 0;
  }

  setLength(size);
  reader_.reset(reader);
  filled_.clear();
  return size;
}

template <typename Sample, int CHANNELS>
block::Size FillableFrameBuffer<Sample, CHANNELS>::doFillNextBlock(
    const block::Block& b) {
  Lock l(lock_);

  if (!reader_) {
    LOG(DFATAL) << "No reader!";
    return 0;
  }

  Samples<44100> size = std::min(block::getSize(b), blockSize_);
  if (!reader_->read(bufferPointers_, CHANNELS, b.first, size.toInt(), false)) {
    LOG(DFATAL) << "Reader failed to read!";
    return 0;
  }

  InterleavedFrame<Sample, CHANNELS>* frame = frames_.frames() + b.first;

  for (int i = 0; i < size; ++i, ++frame) {
    for (int c = 0; c < CHANNELS; ++c) {
      int32 sample = bufferPointers_[c][i];
      convertSample<int32, Sample>(sample, &frame->sample_[c]);
    }
  }

  return size;
}

template class FillableFrameBuffer<short, 2>;

}  // namespace util
}  // namespace audio
}  // namespace rec

