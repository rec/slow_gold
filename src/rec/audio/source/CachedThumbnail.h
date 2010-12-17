#ifndef __REC_AUDIO_SOURCE_CACHEDTHUMBNAIL__
#define __REC_AUDIO_SOURCE_CACHEDTHUMBNAIL__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace source {

class CachedThumbnail
  : public listener::Listener<const AudioSourceChannelInfo&> {
 public:
  CachedThumbnail(const File& file, int compression);
  virtual ~CachedThumbnail();

  juce::AudioThumbnail* thumbnail() { return &thumbnail_; }

  // Update the thumbnail here.
  virtual void operator()(const AudioSourceChannelInfo& info);

 private:
  void writeThumbnail(bool deferred);

  const File file_;
  juce::AudioThumbnail thumbnail_;
  AudioFormatManager manager_;
  juce::AudioThumbnailCache cache_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(CachedThumbnail);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_CACHEDTHUMBNAIL__
