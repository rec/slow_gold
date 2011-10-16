#include "rec/audio/util/FillableFrameBuffer.h"
#include "rec/audio/util/ConvertSample.h"

namespace rec {
namespace audio {
namespace util {

template <typename Sample, int CHANNELS>
FillableFrameBuffer<Sample, CHANNELS>::FillableFrameBuffer(int blockSize)
    : blockSize_(blockSize) {
  for (int i = 0; i < CHANNELS; ++i) {
    buffer_[i].resize(blockSize);
    bufferPointers_[i] = &buffer_[i][0];
  }
}

template <typename Sample, int CHANNELS>
bool FillableFrameBuffer<Sample, CHANNELS>::setReader(
    AudioFormatReader* reader) {
  ScopedLock l(lock_);
  if (!reader) {
    reader_.reset();
    return true;
  }

  Samples<44100> size = reader->lengthInSamples;
  if (!frames_.setLength(size)) {
    LOG(ERROR) << "Unable to set frame length";
    return false;
  }

  setLength(size);
  reader_.reset(reader);
  filled_.clear();
  return true;
}

template <typename Sample, int CHANNELS>
block::Size FillableFrameBuffer<Sample, CHANNELS>::doFillNextBlock(
    const block::Block& b) {
  ScopedLock l(lock_);

  if (!reader_) {
    LOG(ERROR) << "No reader!";
    return 0;
  }

  Samples<44100> size = std::min(block::getSize(b), blockSize_);
  if (!reader_->read(bufferPointers_, CHANNELS, b.first, size.toInt(), false)) {
    LOG(ERROR) << "Reader failed to read!";
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

