#include "rec/audio/util/TrackBufferAndThumbnail.h"
#include "rec/base/Samples.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/audio/util/MakeBufferedReader.h"

using namespace juce;

namespace rec {
namespace audio {
namespace util {

static const char* FILENAME = "thumbnail.stream";

TrackBufferAndThumbnail::TrackBufferAndThumbnail()
    : reader_(makeBufferedReader<short, 2>()) {
}

TrackBufferAndThumbnail::~TrackBufferAndThumbnail() {}

Samples<44100> TrackBufferAndThumbnail::setReader(const VirtualFile& f, AudioFormatReader* reader) {
  Lock l(lock_);
  DCHECK(reader);
  DCHECK(reader->lengthInSamples);
  file_ = getShadowFile(f, FILENAME);
  thumbnail_.read(file_, reader->lengthInSamples);
  return reader_->setReader(reader);
}

}  // namespace util
}  // namespace audio
}  // namespace rec

