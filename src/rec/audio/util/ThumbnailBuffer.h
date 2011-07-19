#ifndef __REC_AUDIO_UTIL_THUMBNAILBUFFER__
#define __REC_AUDIO_UTIL_THUMBNAILBUFFER__

// #define COMPACT_BUFFERS

#include "rec/audio/util/Frame.h"
#include "rec/audio/util/GenericFillableBuffer.h"

#ifdef COMPACT_BUFFERS


#else

#include "rec/audio/util/FillableBuffer.h"

#endif

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail;

#ifdef COMPACT_BUFFERS
  typedef GenericFillableBuffer<short, 2> ThumbnailFillableBuffer;
#else
  typedef FillableBuffer ThumbnailFillableBuffer;
#endif

class ThumbnailBuffer {
 public:
  ThumbnailBuffer(const VirtualFile& file);
  virtual ~ThumbnailBuffer();
  CachedThumbnail* thumbnail() { return thumbnail_.get(); }
  void writeThumbnail();

  ThumbnailFillableBuffer *buffer() { return &buffer_; }

 private:
  PositionableAudioSource* makeSource(const VirtualFile& file);

  ptr<CachedThumbnail> thumbnail_;
  ThumbnailFillableBuffer buffer_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(ThumbnailBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_THUMBNAILBUFFER__
