#ifndef __REC_AUDIO_UTIL_THUMBNAILBUFFER__
#define __REC_AUDIO_UTIL_THUMBNAILBUFFER__

#include "rec/audio/util/Frame.h"
#include "rec/audio/util/FillableFrameBuffer.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail;

typedef FillableFrameBuffer<short, 2> ThumbnailFillableBuffer;

class ThumbnailBuffer : public Listener<const AudioSourceChannelInfo&>,
                        public Broadcaster<juce::AudioThumbnail*> {
 public:
  ThumbnailBuffer();
  virtual ~ThumbnailBuffer();

  ThumbnailFillableBuffer *buffer() { return &buffer_; }

  bool setReader(const VirtualFile& file);
  void setFile(const File& file, int sampleLength);

  virtual void addListener(Listener<juce::AudioThumbnail*>*);

  // Update the thumbnail here.
  virtual void operator()(const AudioSourceChannelInfo& info);

  void writeThumbnail();
  bool cacheWritten() const { return cacheWritten_; }
  juce::AudioThumbnail* thumbnail() { return &thumbnail_; }

 private:
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
