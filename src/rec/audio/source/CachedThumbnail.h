#ifndef __REC_AUDIO_SOURCE_CACHEDTHUMBNAIL__
#define __REC_AUDIO_SOURCE_CACHEDTHUMBNAIL__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace source {

class CachedThumbnail
  : public listener::Listener<const AudioSourceChannelInfo&>,
    public listener::Broadcaster<const juce::AudioThumbnail&> {
 public:
      CachedThumbnail(const File& file, int compression, int sampleLength);
  virtual ~CachedThumbnail();

  juce::AudioThumbnail* thumbnail() { return &thumbnail_; }

  // Update the thumbnail here.
  virtual void operator()(const AudioSourceChannelInfo& info);

  void writeThumbnail(bool deferred);

  bool isFull() const { return written_; }

 private:
  const File file_;
  juce::AudioThumbnail thumbnail_;
  AudioFormatManager manager_;
  juce::AudioThumbnailCache cache_;
  bool written_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(CachedThumbnail);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_CACHEDTHUMBNAIL__
