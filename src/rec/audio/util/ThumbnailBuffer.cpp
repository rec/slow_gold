#include "rec/audio/util/ThumbnailBuffer.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/base/SamplePosition.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace audio {
namespace util {

static const int COMPRESSION = source::RunnyProto().compression();

ThumbnailBuffer::ThumbnailBuffer() : CachedThumbnail(COMPRESSION) {}
ThumbnailBuffer::~ThumbnailBuffer() {}

bool ThumbnailBuffer::setReader(const VirtualFile& f) {
  ptr<AudioFormatReader> reader(source::createReaderAndLoadMetadata(f));
  if (reader) {
    File shadow = getShadowFile(f, "thumbnail.stream");
    setFile(shadow, reader->lengthInSamples);
  } else if (!file::empty(f)) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
  }
  return buffer_.setReader(reader.transfer());
}

}  // namespace util
}  // namespace audio
}  // namespace rec

