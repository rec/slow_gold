#ifndef __REC_AUDIO_UTIL_FILEBUFFER__
#define __REC_AUDIO_UTIL_FILEBUFFER__

#include "rec/audio/util/FillableBuffer.h"

namespace rec {
namespace audio {
namespace util {

class CachedThumbnail;

class FileBuffer : public FillableBuffer {
 public:
  FileBuffer(const VirtualFile& file);
  virtual ~FileBuffer();
  CachedThumbnail* thumbnail() { return thumbnail_.get(); }

 private:
  ptr<CachedThumbnail> thumbnail_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(FileBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FILEBUFFER__
