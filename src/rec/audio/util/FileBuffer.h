#ifndef __REC_AUDIO_UTIL_FILEBUFFER__
#define __REC_AUDIO_UTIL_FILEBUFFER__

#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/util/CachedThumbnail.h"
#include "rec/audio/util/FillableBuffer.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {
namespace util {

struct FileBuffer {
  typedef source::RunnyProto RunnyProto;

  FileBuffer(const VirtualFile& file,
             const RunnyProto& desc = RunnyProto::default_instance());

  ptr<CachedThumbnail> thumbnail_;
  ptr<FillableBuffer> buffer_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(FileBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FILEBUFFER__
