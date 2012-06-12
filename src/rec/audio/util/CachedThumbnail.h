#ifndef __REC_AUDIO_UTIL_CACHEDTHUMBNAIL__
#define __REC_AUDIO_UTIL_CACHEDTHUMBNAIL__

#include "rec/audio/Audio.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail {
 public:
  CachedThumbnail();

  void addBlock(SampleTime pos, const AudioSourceChannelInfo& info);
  AudioThumbnail* thumbnail() { return &thumbnail_; }
  bool cacheWritten() const { return cacheWritten_; }
  void write(const File&);
  void read(const File&, int64 sampleLength,
            int channels = 2, float sampleRate = 44100.0f);

 private:
  bool cacheWritten_;

  AudioThumbnailCache cache_;
  AudioThumbnail thumbnail_;

  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CachedThumbnail);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_CACHEDTHUMBNAIL__
