#ifndef __REC_AUDIO_UTIL_THUMBNAILBUFFER__
#define __REC_AUDIO_UTIL_THUMBNAILBUFFER__

#include "rec/audio/util/GenericFillableBuffer.h"
#include "rec/audio/util/FillableBuffer.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail;

#ifndef NEW
class ThumbnailBuffer : public FillableBuffer {
#else
class ThumbnailBuffer : public GenericFillableBuffer<short, 2> {
#endif
 public:
  ThumbnailBuffer(const VirtualFile& file);
  virtual ~ThumbnailBuffer();
  CachedThumbnail* thumbnail() { return thumbnail_.get(); }
  void writeThumbnail();

 private:
  ptr<CachedThumbnail> thumbnail_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(ThumbnailBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_THUMBNAILBUFFER__
