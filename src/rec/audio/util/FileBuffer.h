#ifndef __REC_AUDIO_UTIL_FILEBUFFER__
#define __REC_AUDIO_UTIL_FILEBUFFER__

#include "rec/base/base.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/gui/audio/CachedThumbnail.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/util/FillableBuffer.h"

namespace rec {
namespace audio {
namespace util {

class FileBuffer {
 public:
  typedef source::RunnyProto RunnyProto;
  typedef gui::audio::CachedThumbnail CachedThumbnail;
  typedef audio::util::FillableBuffer FillableBuffer;

  FileBuffer(const VirtualFile& file,
             const RunnyProto& desc = RunnyProto::default_instance());

  CachedThumbnail* thumbnail() { return thumbnail_.get(); }
  FillableBuffer* buffer() { return buffer_.get(); }

 private:
  ptr<CachedThumbnail> thumbnail_;
  ptr<FillableBuffer> buffer_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(FileBuffer);
};

}  // namespace util
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_UTIL_FILEBUFFER__
