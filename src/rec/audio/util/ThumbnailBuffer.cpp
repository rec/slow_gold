#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/audio/util/CachedThumbnail.h"
#include "rec/base/SamplePosition.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {
namespace util {

ThumbnailBuffer::~ThumbnailBuffer() {
  DLOG(ERROR) << "Deleting thumbnail buffer";
}

ThumbnailBuffer::ThumbnailBuffer(const VirtualFile& f) {
  ptr<PositionableAudioSource> source(source::createSourceAndLoadMetadata(f));
  if (!source) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }
  File shadow = getShadowFile(f, "thumbnail.stream");
  int len = source->getTotalLength();
  static source::RunnyProto d;
  thumbnail_.reset(new CachedThumbnail(shadow, d.compression(), len));
  if (!thumbnail_->cacheWritten())
    source.reset(source::Snoopy::add(source.transfer(), thumbnail_.get()));

  setSource(source.transfer());
}

void ThumbnailBuffer::writeThumbnail() { thumbnail_->writeThumbnail(); }


}  // namespace util
}  // namespace audio
}  // namespace rec

