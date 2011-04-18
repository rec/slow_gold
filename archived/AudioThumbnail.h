#ifndef __REC_GUI_AUDIOTHUMBNAIL__
#define __REC_GUI_AUDIOTHUMBNAIL__

#include "rec/util/listener/Listener.h"
#include "rec/audio/util/AudioFormatManager.h"

namespace rec {
namespace gui {

class AudioThumbnail : public juce::AudioThumbnail,
                       public listener::Listener<const AudioSourceChannelInfo&> {
 public:
  AudioThumbnail(const File& file, int compression = 512)
      : juce::AudioThumbnail(compression, getAudioFormatManager() cache_),
        file_(file) {
  }

  virtual void operator()(const AudioSourceChannelInfo& info) {
    addBlock(info.startSample, *info.buffer, info.startSample, info.numSamples);
  }

 private:
  const File file_;
  juce::AudioThumbnailCache cache_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AudioThumbnail);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIOTHUMBNAIL__
