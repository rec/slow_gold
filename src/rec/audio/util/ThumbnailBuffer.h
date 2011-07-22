#ifndef __REC_AUDIO_UTIL_THUMBNAILBUFFER__
#define __REC_AUDIO_UTIL_THUMBNAILBUFFER__

#define COMPACT_BUFFERS

#include "rec/audio/util/Frame.h"
#include "rec/audio/util/FillableFrameBuffer.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail;

#ifdef COMPACT_BUFFERS
  typedef FillableFrameBuffer<short, 2> ThumbnailFillableBuffer;
#else
  typedef FillableBuffer ThumbnailFillableBuffer;
#endif

class ThumbnailBuffer {
 public:
  ThumbnailBuffer();
  virtual ~ThumbnailBuffer();

  CachedThumbnail* thumbnail() { return thumbnail_.get(); }
  void writeThumbnail();

  ThumbnailFillableBuffer *buffer() { return &buffer_; }
  bool setReader(const VirtualFile& file);

 private:
  ptr<CachedThumbnail> thumbnail_;
  ThumbnailFillableBuffer buffer_;

  DISALLOW_COPY_AND_ASSIGN(ThumbnailBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_THUMBNAILBUFFER__
