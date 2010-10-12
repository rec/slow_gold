#ifndef __REC_AUDIO_SOURCE_COPY__
#define __REC_AUDIO_SOURCE_COPY__

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

using namespace juce;

namespace rec {
namespace audio {

// Copy samples from one audio buffer to another.
inline void copySamples(const AudioSampleBuffer& source,
                        int sourceStart,
                        const AudioSourceChannelInfo& destInfo) {
  AudioSampleBuffer* dest = destInfo.buffer;
  int destStart = destInfo.startSample;
  int numSamples = destInfo.numSamples;

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
      int c1 = (sourceChannels * c) / destChannels;
      int c2 = (sourceChannels * (c + 1) - 1) / destChannels;
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

inline int copyCircularSamples(const AudioSampleBuffer& source,
                               int sourceStart,
                               const AudioSourceChannelInfo& dest) {
  AudioSourceChannelInfo block = dest;
  int copied = 0;
  int length = source.getNumSamples();
  sourceStart %= length;
  while (copied < dest.numSamples) {
    block.numSamples = std::min(length - sourceStart, dest.numSamples - copied);
    copySamples(source, sourceStart, block);
    copied += block.numSamples;
    block.startSample = dest.startSample + copied;
    sourceStart = (sourceStart + block.numSamples) % length;
  }
  return sourceStart;
}


}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_COPY__
