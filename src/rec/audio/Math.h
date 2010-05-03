#ifndef __REC_AUDIO_MATH
#define __REC_AUDIO_MATH

#include "juce_amalgamated.h"

namespace rec {
namespace audio {
namespace math {

inline float rampWave(int ramp, int scale) {
  return ((ramp + scale) % (2 * scale + 1) - scale) / float(scale);
}

inline void wraparound(int length, int toWrap, AudioSampleBuffer* buffer) {
  // Make the buffer wrap around a little for ease in shifting...
  float **samples = buffer->getArrayOfChannels();
  int channels = buffer->getNumChannels();

  for (int wrapped = 0; wrapped < toWrap; ) {
    int sampleLength = std::min(toWrap, length);
    int byteLength = sampleLength * sizeof(float);
    for (int c = 0; c < channels; ++c)
      memcpy(samples[c] + length + wrapped, samples[c], byteLength);
  }
}

}  // namespace math
}  // namespace audio
}  // namespace rec


#endif  // __REC_AUDIO_MATH
