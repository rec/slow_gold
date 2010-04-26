#include "rec/buffer/services.h"

namespace rec {
namespace buffer {

typedef Services<AudioSampleBuffer*> JUCEServices;


// NOTE: this will be quadratic in the cases where we keep having to
// increase the buffer size.  TODO(tritchford): come up with a better
// resizing strategy.

Size JUCEServices::setSize(AudioSampleBuffer* buffer, Size size) {
  buffer->setSize(buffer->getNumChannels(), size, true, false, true);
  return size;
}

template <>
Size JUCEServices::copy(AudioSampleBuffer* out, Size outBegin,
                        const AudioSampleBuffer& in, const Block& inBlock) {
  Size inBegin = inBlock.first;
  Size numSamples = jmin(inBlock.second - begin, out->getNumSamples());
  if (numSamples) {
    int channels = jmin(out->getNumChannels(), in.getNumChannels());
    for (int i = 0; i < channels; ++i)
      out->copyFrom(i, outBegin, in, i, inBegin, numSamples);
  }
  return numSamples;
};

}  // namespace buffer
}  // namespace rec

