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
  // TODO: bug Jules
  if (!reader_->read(bufferPointers_, CHANNELS, static_cast<int>(b.first), size,
                     false)) {
    LOG(ERROR) << "Reader failed to read!";
    return 0;
  }

  typename Frames<Sample, CHANNELS>::Frame* frame = frames_.frames() + b.first;

#if 0
  int32 max = std::numeric_limits<int32>::min();
  int32 min = std::numeric_limits<int32>::max();
  DLOG(INFO) << "? min: " << min << ", max: " << max;
#endif

  for (int i = 0; i < size; ++i, ++frame) {
    for (int c = 0; c < CHANNELS; ++c) {
      int32 sample = bufferPointers_[c][i];
      convertSample<int32, Sample>(sample, &frame->sample_[c]);
#if 0
      max = std::max(sample, max);
      min = std::min(sample, min);
      DLOG_EVERY_N(INFO, 3000) << double(sample) / std::numeric_limits<int32>::max() << ", " << frame->sample_[c];
#endif
    }
  }

#if 0
  DLOG(INFO) << "min: " << min << ", max: " << max;
  double m = std::numeric_limits<int32>::max();
  DLOG(INFO) << "min: " << min / m << ", max: " << max / m;
#endif

  return size;
}

template class FillableFrameBuffer<short, 2>;

}  // namespace util
}  // namespace audio
}  // namespace rec

