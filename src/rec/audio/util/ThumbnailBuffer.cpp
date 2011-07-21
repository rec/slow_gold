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

void ThumbnailBuffer::setReader(const VirtualFile& f) {
  ptr<AudioFormatReader> reader(source::createReaderAndLoadMetadata(f));
  if (reader) {
    File shadow = getShadowFile(f, "thumbnail.stream");
    static source::RunnyProto d;
    thumbnail_.reset(new CachedThumbnail(shadow, d.compression(), reader->lengthInSamples));
    buffer_.setReader(reader.transfer());
  } else {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
  }
}

ThumbnailBuffer::ThumbnailBuffer() {}

void ThumbnailBuffer::writeThumbnail() {
  if (thumbnail_)
    thumbnail_->writeThumbnail();
  else
    LOG(ERROR) << "Writing an empty thumbnail";
}

}  // namespace util
}  // namespace audio
}  // namespace rec

