#ifndef __REC_AUDIO_SOURCE_COPY__
#define __REC_AUDIO_SOURCE_COPY__

#include "juce_amalgamated.h"
#include "rec/audio/source/new/Wrapper.h"
#include "rec/util/Circular.h"

namespace rec {
namespace audio {
namespace source {

inline void copy(int numSamples,
                 int sourceStart,
                 const AudioSampleBuffer& source,
                 int destStart,
                 AudioSampleBuffer* dest) {
  int sourceChannels = source.getNumChannels();
  int destChannels = dest->getNumChannels();

  if (sourceChannels == 1) {
    float* samples = source.getSampleData(0, sourceStart);
    for (int c = 0; c < destChannels; ++c)
      dest->copyFrom(c, destStart, samples, numSamples);

  } else if (destChannels == sourceChannels) {
    for (int c = 0; c < destChannels; ++c)
      dest->copyFrom(c, destStart, source, c, sourceStart, numSamples);

  } else {
    for (int c = 0; c < destChannels; ++c) {
      int c1 = (channels * c) / destChannels;
      int c2 = (channels * (c + 1) - 1) / destChannels;
      float* samples = source.getSampleData(c1, sourceStart);
      if (c1 == c2) {
        dest->copyFrom(c, destStart, samples, numSamples);
      } else {
        dest->copyFrom(c, destStart, samples, numSamples, 0.5);
        dest->addFrom(c, destStart, source, c2, sourceStart, numSamples, 0.5);
      }
    }
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_COPY__
