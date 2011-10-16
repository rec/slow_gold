#include "rec/audio/util/Frame.h"
#include "rec/audio/util/ConvertSample.h"
#include "rec/util/Platform.h"

namespace rec {
namespace audio {

template <typename Frame>
bool Frames<Frame>::setLength(Samples<44100> length, bool mustReallocate) {
  if (length != length_ && (mustReallocate || length > allocatedLength_)) {
    allocatedLength_ = length;
    size_t size = static_cast<size_t>(sizeof(Frame) * length);
    frames_ = reinterpret_cast<Frame*>(reallocf(frames_, size));
  }
  length_ = length;
  return !length_ || frames_;
}

template <typename Sample, int CHANNELS>
void fillArrayOfChannels(InterleavedFrame<Sample, CHANNELS>* in,
                         Samples<44100> inOffset,
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
Samples<44100> Frames<Frame>::getAudioBlock(const Info& info,
                                            Samples<44100> offset) const {
  int numSamples = std::min(info.numSamples, static_cast<int>(length_ - offset));
  float** out = info.buffer->getArrayOfChannels();
  fillArrayOfChannels(frames_, offset, out, info.startSample, numSamples);
  return numSamples;
}

template class Frames<CDFrame>;
template class Frames<FloatFrame>;

}  // namespace audio
}  // namespace rec
