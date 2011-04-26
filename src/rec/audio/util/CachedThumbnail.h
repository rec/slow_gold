#ifndef __REC_AUDIO_UTIL_CACHEDTHUMBNAIL__
#define __REC_AUDIO_UTIL_CACHEDTHUMBNAIL__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail
  : public Listener<const AudioSourceChannelInfo&>, public Broadcaster<bool> {
 public:
  CachedThumbnail(const File& file, int compression, int sampleLength);
  virtual ~CachedThumbnail();

  juce::AudioThumbnail* thumbnail() { return &thumbnail_; }

  // Update the thumbnail here.
  virtual void operator()(const AudioSourceChannelInfo& info);

  void writeThumbnail();

  bool cacheWritten() const { return cacheWritten_; }

 private:
  const File file_;
  juce::AudioThumbnail thumbnail_;
  juce::AudioThumbnailCache cache_;
  bool cacheWritten_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(CachedThumbnail);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_CACHEDTHUMBNAIL__
