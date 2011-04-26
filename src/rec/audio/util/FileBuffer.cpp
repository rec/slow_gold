#include "rec/audio/util/FileBuffer.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/source/Snoopy.h"

namespace rec {
namespace audio {
namespace util {

FileBuffer::FileBuffer(const VirtualFile& f, const RunnyProto& desc) {
  ptr<PositionableAudioSource> source(source::createSourceAndLoadMetadata(f));
  if (!source) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }
  File shadow = getShadowFile(f, "thumbnail.stream");
  int len = source->getTotalLength();
  RunnyProto d;
  thumbnail_.reset(new CachedThumbnail(shadow, d.compression(), len));
  if (!thumbnail_->cacheWritten())
    source.reset(source::Snoopy::add(source.transfer(), thumbnail_.get()));

  buffer_.reset(new FillableBuffer(source.transfer(), d.chunk_size()));
}

}  // namespace util
}  // namespace audio
}  // namespace rec
