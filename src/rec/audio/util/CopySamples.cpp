#include "rec/audio/util/CopySamples.h"

namespace rec {
namespace audio {

// Copy samples from one audio buffer to another.
void copySamples(const AudioSampleBuffer& source,
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

int copyCircularSamples(const AudioSampleBuffer& source,
                        int sourceStart,
                        const AudioSourceChannelInfo& dest,
                        int64 ready) {
  AudioSourceChannelInfo info = dest;
  if (ready != -1 && ready < info.numSamples) {
    LOG(ERROR) << "clearing " << info.numSamples - ready
               << ", getting " << ready;

    info.buffer->clear(info.startSample + ready, info.numSamples - ready);
    info.numSamples = ready;
  }

  int copied = 0;
  int length = source.getNumSamples();
  int nextFree = sourceStart % length;

#if 0
  DLOG(INFO) << "copy " << info.numSamples
             << " from: " << &source <<  ":" << source.getNumSamples()
             << ", " << sourceStart
             << " to: " << info.buffer << ":" << info.buffer->getNumSamples()
             << ", " << info.startSample;
#endif
  while (copied < dest.numSamples) {
    info.numSamples = std::min(length - nextFree, dest.numSamples - copied);
    copySamples(source, nextFree, info);
    copied += info.numSamples;
    info.startSample = dest.startSample + copied;
    nextFree = (nextFree + info.numSamples) % length;
  }

  return nextFree;
}

}  // namespace audio
}  // namespace rec
