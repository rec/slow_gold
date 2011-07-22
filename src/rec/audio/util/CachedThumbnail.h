#ifndef __REC_AUDIO_UTIL_CACHEDTHUMBNAIL__
#define __REC_AUDIO_UTIL_CACHEDTHUMBNAIL__

#include "rec/util/listener/Listener.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail : public Listener<const AudioSourceChannelInfo&>,
                        public Broadcaster<juce::AudioThumbnail*> {
 public:
  CachedThumbnail(const File& file, int compression, int sampleLength);
  virtual ~CachedThumbnail();

  void setFile(const File& file, int sampleLength);

  juce::AudioThumbnail* thumbnail() { return thumbnail_.get(); }
  virtual void addListener(Listener<juce::AudioThumbnail*>*);

  // Update the thumbnail here.
  virtual void operator()(const AudioSourceChannelInfo& info);

  void writeThumbnail();
  bool cacheWritten() const { return cacheWritten_; }

 private:
  File file_;
  const int compression_;

  ptr<juce::AudioThumbnail> thumbnail_;
  juce::AudioThumbnailCache cache_;
  bool cacheWritten_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(CachedThumbnail);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_CACHEDTHUMBNAIL__
