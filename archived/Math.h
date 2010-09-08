#ifndef __REC_AUDIO_MATH
#define __REC_AUDIO_MATH

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace audio {
namespace math {

template <typename Sample>
inline void wraparound(int length, int toWrap, Sample* samples) {
  for (int wrapped = 0; wrapped < toWrap; ) {
    int sampleLength = std::min(toWrap, length);
    memcpy(samples + length + wrapped, samples, sampleLength * sizeof(Sample));
    wrapped += sampleLength;
  }
}

template <typename Sample>
inline void wraparound(int length, int toWrap, Sample** begin, Sample** end) {
  for (Sample** f = begin; f != end; ++f)
    wraparound(length, toWrap, f);
}


inline void wraparound(int length, int toWrap, AudioSampleBuffer* b) {
  float** begin = b->getArrayOfChannels();
  wraparound(length, toWrap, begin, begin + b->getNumChannels());
}

}  // namespace math
}  // namespace audio
}  // namespace rec


#endif  // __REC_AUDIO_MATH
