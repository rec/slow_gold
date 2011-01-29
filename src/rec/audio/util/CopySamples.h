#ifndef __REC_AUDIO_SOURCE_COPY__
#define __REC_AUDIO_SOURCE_COPY__

#include "rec/base/base.h"

using namespace juce;

namespace rec {
namespace audio {

// Copy samples from one audio buffer to another.
void copySamples(const AudioSampleBuffer& source,
                 int sourceStart,
                 const AudioSourceChannelInfo& destInfo);

int copyCircularSamples(const AudioSampleBuffer& source,
                        int sourceStart,
                        const AudioSourceChannelInfo& dest);

}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_COPY__
