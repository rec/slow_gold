#pragma once

#include "rec/base/SampleRate.h"
#include "rec/audio/Audio.h"
#include "rec/base/SampleTime.h"

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
  void read(const File&, SampleRate rate, SampleTime sampleLength, int channels = 2);

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

