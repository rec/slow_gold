#include "rec/audio/util/FillableFrameBuffer.h"
#include "rec/audio/util/ConvertSample.h"
#include "rec/audio/source/FrameSource.h"

namespace rec {
namespace audio {
namespace util {

template <typename Sample, int CHANNELS>
FillableFrameBuffer<Sample, CHANNELS>::FillableFrameBuffer(int blockSize)
    : blockSize_(blockSize), intBuffer_(blockSize), floatBuffer_(blockSize) {
  CHECK_DDD(194, 439, int64, int64);
}

template <typename Sample, int CHANNELS>
bool FillableFrameBuffer<Sample, CHANNELS>::setLength(int64 length) {
  bool success = frames_.setLength(length);
  Fillable::setLength(success ? length : 0);
  return success;
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

  int32** pointers = reader_->usesFloatingPointData ?
    reinterpret_cast<int32**>(floatBuffer_.pointers_) : intBuffer_.pointers_;

  if (!reader_->read(pointers, CHANNELS, b.first, size.toInt(), false)) {
    LOG(DFATAL) << "Reader failed to read!";
    return 0;
  }

  InterleavedFrame<Sample, CHANNELS>* frame = frames_.frames() + b.first;

  for (int i = 0; i < size; ++i, ++frame) {
    for (int c = 0; c < CHANNELS; ++c) {
      if (reader_->usesFloatingPointData) {
        float sample = floatBuffer_.pointers_[c][i];
        convertSample<float, Sample>(sample, &frame->sample_[c]);
      } else {
        int32 sample = intBuffer_.pointers_[c][i];
        convertSample<int32, Sample>(sample, &frame->sample_[c]);
      }
    }
  }

  return size;
}

template <typename Sample, int CHANNELS>
Source* FillableFrameBuffer<Sample, CHANNELS>::makeSource() const {
  return new source::FrameSource<Sample, CHANNELS>(frames_);
}

template class FillableFrameBuffer<short, 2>;

}  // namespace util
}  // namespace audio
}  // namespace rec

