#include "rec/audio/util/Frame.h"
#include "rec/audio/util/ConvertSample.h"

namespace rec {
namespace audio {

template <typename Sample, int CHANNELS>
bool Frames<Sample, CHANNELS>::setLength(SamplePosition length) {
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

template <typename Sample, int CHANNELS>
SamplePosition Frames<Sample, CHANNELS>::getAudioBlock(const Info& info,
                                                       SamplePosition offset) const {
  int numSamples = std::min(info.numSamples, static_cast<int>(length_ - offset));
  float** out = info.buffer->getArrayOfChannels();
  Frame* frame = frames_ + offset;
  for (int i = 0, s = info.startSample; i < numSamples; ++i, ++frame, ++s) {
    for (int ch = 0; ch < CHANNELS; ++ch)
      convertSample<Sample, float>(frame->sample_[ch], &(out[ch][s]));
  }

  return numSamples;
}

template class Frames<short, 2>;

}  // namespace audio
}  // namespace rec
