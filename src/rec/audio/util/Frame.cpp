#include "rec/audio/util/Frame.h"
#include "rec/audio/util/ConvertSample.h"
#include "rec/util/Platform.h"

namespace rec {
namespace audio {

template <typename Frame>
Frames<Frame>::Frames(SampleTime length)
    : length_(-1), allocatedLength_(-1), frames_(NULL) {
  setLength(length);
}


template <typename Frame>
bool Frames<Frame>::setLength(SampleTime length, bool mustReallocate) {
  if (length != length_ && (mustReallocate || length > allocatedLength_)) {
    allocatedLength_ = length;
    size_t size = static_cast<size_t>(sizeof(Frame) * length);
    void *f = realloc(frames_, size);
    DCHECK(!size || f) << "Couldn't allocate " << size;

    frames_ = reinterpret_cast<Frame*>(f);
	  DCHECK(!size || frames_) << "Couldn't cast " << size;
  }
  bool success = !length || frames_;
  if (!success)
    LOG(DFATAL) << "Couldn't setLength: " << length << ", " << frames_;
  length_ = length;

  return success;
}

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

template <typename Frame>
SampleTime Frames<Frame>::getAudioBlock(const Info& info,
                                            SampleTime offset) const {
  int numSamples = std::min(info.numSamples, static_cast<int>(length_ - offset));
  float** out = info.buffer->getArrayOfChannels();
  DCHECK_GE(numSamples, 0) << info.numSamples << ", " << length_ << ", "  << offset;
  fillArrayOfChannels(frames_, offset, out, info.startSample, numSamples);
  return numSamples;
}

template class Frames<CDFrame>;
template class Frames<FloatFrame>;

}  // namespace audio
}  // namespace rec
