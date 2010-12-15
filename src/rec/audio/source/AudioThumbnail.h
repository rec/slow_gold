#ifndef __REC_AUDIO_SOURCE_AUDIOTHUMBNAIL__
#define __REC_AUDIO_SOURCE_AUDIOTHUMBNAIL__

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace source {

class AudioThumbnail : public juce::AudioThumbnail,
                       public listener::Listener<const AudioSourceChannelInfo&> {
 public:
  AudioThumbnail(const File& file, int compression = 512)
      : juce::AudioThumbnail(compression, manager_, cache_), file_(file) {}

  virtual void operator()(const AudioSourceChannelInfo& info) {
    addBlock(info.startSample, *info.buffer, info.startSample, info.numSamples);
  }

 private:
  const File file_;
  AudioFormatManager manager_;
  juce::AudioThumbnailCache cache_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AudioThumbnail);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_AUDIOTHUMBNAIL__
