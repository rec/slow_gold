#ifndef __REC_AUDIO_UTIL_THUMBNAILBUFFER__
#define __REC_AUDIO_UTIL_THUMBNAILBUFFER__

#include "rec/audio/util/FillableBuffer.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail;

class ThumbnailBuffer : public FillableBuffer {
 public:
  ThumbnailBuffer(const VirtualFile& file);
  virtual ~ThumbnailBuffer();
  CachedThumbnail* thumbnail() { return thumbnail_.get(); }

 private:
  ptr<CachedThumbnail> thumbnail_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(ThumbnailBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_THUMBNAILBUFFER__
