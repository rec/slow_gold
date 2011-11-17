#ifndef __REC_AUDIO_UTIL_THUMBNAILBUFFER__
#define __REC_AUDIO_UTIL_THUMBNAILBUFFER__

#include "rec/audio/util/Frame.h"
#include "rec/audio/util/FillableFrameBuffer.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail;

class ThumbnailBuffer {
 public:
  ThumbnailBuffer();
  virtual ~ThumbnailBuffer();

  FillableFrameBuffer<short, 2> *buffer() { return &buffer_; }

  bool setReader(const VirtualFile& file, AudioFormatReader* r);
  void setFile(const File& file, int sampleLength);

  void addBlock(Samples<44100> pos, const AudioSourceChannelInfo& info);

  void writeThumbnail();
  bool cacheWritten() const { return cacheWritten_; }
  juce::AudioThumbnail* thumbnail() { return &thumbnail_; }

 private:
  CriticalSection lock_;

  File file_;
  juce::AudioThumbnailCache cache_;
  bool cacheWritten_;
  juce::AudioThumbnail thumbnail_;

  FillableFrameBuffer<short, 2> buffer_;

  DISALLOW_COPY_AND_ASSIGN(ThumbnailBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_THUMBNAILBUFFER__
