#include "rec/audio/util/FillableFrameBuffer.h"

#include "rec/audio/source/FrameSource.h"
#include "rec/audio/util/ConvertSample.h"
#include "rec/audio/util/Frame.h"
#include "rec/base/Samples.h"

namespace rec {
namespace audio {
namespace util {

namespace {

template <typename Sample, int CHANNELS>
struct SampleBuffer {
  SampleBuffer(int sampleCount) {
    for (int i = 0; i < CHANNELS; ++i) {
      buffer_[i].resize(sampleCount);
      pointers_[i] = &buffer_[i][0];
    }
  }

  vector<Sample> buffer_[CHANNELS];
  Sample* pointers_[CHANNELS];
};

template <typename Sample, int CHANNELS>
class FillableFrameBuffer : public BufferedReader {
 public:
  FillableFrameBuffer(int s) : blockSize_(s), intBuffer_(s), floatBuffer_(s) {
    CHECK_DDD(194, 439, int64, int64);
  }

  virtual ~FillableFrameBuffer() {}

  // Returns the length in samples, or 0 if there's an error.
  virtual block::Size doFillNextBlock(const block::Block& b) {
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

  typedef Frames<InterleavedFrame<Sample, CHANNELS> > FillableFrame;

  virtual Source* makeSource() const {
    return new source::FrameSource<Sample, CHANNELS>(frames_);
  }

  virtual bool setLength(int64 length) {
    bool success = frames_.setLength(length);
    Fillable::setLength(success ? length : 0);
    return success;
  }

  const FillableFrame& frames() const { return frames_; }

 protected:
  virtual void onFilled() { reader_.reset(); }

 private:
  CriticalSection lock_;

  const block::Size blockSize_;
  FillableFrame frames_;

  SampleBuffer<int32, CHANNELS> intBuffer_;
  SampleBuffer<float, CHANNELS> floatBuffer_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(FillableFrameBuffer);
};

}  // namespace

template <typename Sample, int CHANNELS>
BufferedReader* makeBufferedReader(int size) {
  return new FillableFrameBuffer<Sample, CHANNELS>(size);
}

template BufferedReader* makeBufferedReader<short, 2>(int);

}  // namespace util
}  // namespace audio
}  // namespace rec

