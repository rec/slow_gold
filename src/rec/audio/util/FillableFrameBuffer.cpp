#include "rec/audio/util/FillableFrameBuffer.h"

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

  SamplePosition size = reader->lengthInSamples;
  if (!frames_.setLength(size))
    return false;

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

  SamplePosition size = std::min(block::getSize(b), blockSize_);
  if (!reader_->read(bufferPointers_, CHANNELS, b.first, size, false)) {
    LOG(ERROR) << "Reader failed to read!";
    return 0;
  }

  typename Frames<Sample, CHANNELS>::Frame* frame = frames_.frames();
  for (int i = 0; i < size; ++i, ++frame) {
    for (int c = 0; c < CHANNELS; ++c)
      convertSample(bufferPointers_[c][i], &frame->sample_[c]);
  }

  return size;
}

template class FillableFrameBuffer<short, 2>;

}  // namespace util
}  // namespace audio
}  // namespace rec

