#ifndef __REC_AUDIO_UTIL_THUMBNAILBUFFER__
#define __REC_AUDIO_UTIL_THUMBNAILBUFFER__

#include "rec/audio/util/CachedThumbnail.h"
#include "rec/audio/util/Frame.h"
#include "rec/audio/util/FillableFrameBuffer.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail;

typedef FillableFrameBuffer<short, 2> ThumbnailFillableBuffer;

class ThumbnailBuffer : public CachedThumbnail {
 public:
  ThumbnailBuffer();
  virtual ~ThumbnailBuffer();

  ThumbnailFillableBuffer *buffer() { return &buffer_; }
  bool setReader(const VirtualFile& file);

 private:
  FillableFrameBuffer<short, 2> buffer_;

  DISALLOW_COPY_AND_ASSIGN(ThumbnailBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_THUMBNAILBUFFER__
