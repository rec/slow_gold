#include "rec/audio/util/Frame.h"
#include "rec/audio/util/ConvertSample.h"

namespace rec {
namespace audio {

template <typename Frame>
bool Frames<Frame>::setLength(SamplePosition length) {
  free(frames_);

  // TODO: fix this for really large buffers.
  void* mem = malloc(static_cast<size_t>(sizeof(Frame) * length));
  if (!mem) {
    LOG(ERROR) << "Not enough memory, sample length: " << length;
    length_ = 0;
    return false;
  }
  frames_ = reinterpret_cast<Frame*>(mem);
  length_ = length;
  return true;
}

template <typename Frame>
void fillArrayOfChannels(Frame* in, SamplePosition inOffset,
                         float **out, int outOffset,
                         int numSamples);

template <typename Sample, int CHANNELS>
void fillArrayOfChannels(InterleavedFrame<Sample, CHANNELS>* in,
                         SamplePosition inOffset,
                         float **out, int outOffset,
                         int numSamples) {
  typedef InterleavedFrame<Sample, CHANNELS> Frame;
  Frame* frame = in + inOffset;
  for (int i = 0, s = outOffset; i < numSamples; ++i, ++frame, ++s) {
    for (int ch = 0; ch < CHANNELS; ++ch)
      convertSample<Sample, float>(frame->sample_[ch], &(out[ch][s]));
  }
}

template <typename Frame>
SamplePosition Frames<Frame>::getAudioBlock(const Info& info,
                                            SamplePosition offset) const {
  int numSamples = std::min(info.numSamples, static_cast<int>(length_ - offset));
  float** out = info.buffer->getArrayOfChannels();
  fillArrayOfChannels(frames_, offset, out, info.startSample, numSamples);
  return numSamples;
}

template class Frames<CDFrame>;

}  // namespace audio
}  // namespace rec
