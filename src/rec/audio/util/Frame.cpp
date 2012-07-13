#include "rec/audio/util/Frame.h"
#include "rec/audio/util/ConvertSample.h"
#include "rec/util/Platform.h"

namespace rec {
namespace audio {

namespace {

template <typename Sample, int CHANNELS>
void fillArrayOfChannels(InterleavedFrame<Sample, CHANNELS>* in,
                         SampleTime inOffset,
                         float **out, int outOffset,
                         int numSamples) {
  typedef InterleavedFrame<Sample, CHANNELS> Frame;
  Frame* frame = in + inOffset.toInt();
  for (int i = 0, s = outOffset; i < numSamples; ++i, ++frame, ++s) {
    for (int ch = 0; ch < CHANNELS; ++ch)
      convertSample<Sample, float>(frame->sample_[ch], &(out[ch][s]));
  }
}

}  // namespace

template <typename Frame>
Frames<Frame>::Frames(SampleTime length)
    : length_(0), allocatedLength_(0), frames_(NULL) {
  setLength(length);
}


template <typename Frame>
bool Frames<Frame>::setLength(SampleTime length) {
  if (length == length_)
    return true;

  if (length <= allocatedLength_) {
    length_ = length;
    return true;
  }

  size_t size = static_cast<size_t>(sizeof(Frame) * length);
  if (void *f = realloc(frames_, size)) {
    frames_ = reinterpret_cast<Frame*>(f);
    allocatedLength_ = length_ = length;
    return true;
  } else {
    LOG(ERROR) << "Unable to allocate " << length << " frames, "
               << size << " bytes ";
    return false;
  }
}

template <typename Frame>
SampleTime Frames<Frame>::getAudioBlock(const Info& info,
                                        SampleTime offset) const {
  int numSamples = std::min(info.numSamples, static_cast<int>(length_ - offset));
  float** out = info.buffer->getArrayOfChannels();
  DCHECK_GE(numSamples, 0) << info.numSamples << ", " << length_ << ", "  << offset;
  fillArrayOfChannels(frames_, offset, out, info.startSample, numSamples);
  return numSamples;
}

template class Frames< InterleavedFrame<short, 2> >;
template class Frames< InterleavedFrame<float, 2> >;


#if 0

template <typename Sample, int CHANNELS>
struct ParallelFrame {
  ParallelFrame() : channels_(CHANNELS), sample_(NULL) {}
  ParallelFrame(Sample** sample) : channels_(CHANNELS), sample_(sample) {}

  const int channels_;
  Sample** sample_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(ParallelFrame);
};
#endif

}  // namespace audio
}  // namespace rec
