#ifndef __REC_AUDIO_SOURCE_AUDIOTHUMBNAIL__
#define __REC_AUDIO_SOURCE_AUDIOTHUMBNAIL__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

class AudioThumbnail : public juce::AudioThumbnail {
 public:
  AudioThumbnail(int sourceSamplesPerThumbnailSample)
      : juce::AudioThumbnail(sourceSamplesPerThumbnailSample,
                             formatManager_, cache_) {
  }

 private:
  AudioFormatManager formatManager_;
  juce::AudioThumbnailCache cache_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AudioThumbnail);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_AUDIOTHUMBNAIL__
