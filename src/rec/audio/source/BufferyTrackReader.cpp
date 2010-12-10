#include "rec/audio/source/BufferyTrackReader.h"
#include "rec/audio/source/TrackReader.h"

namespace rec {
namespace audio {
namespace source {

BufferySourceFactory::BufferySourceFactory(const VolumeFile& f, int blockSize)
    : Buffery(createReader(f), blockSize), duringShutdown_(false) {
}

Source* BufferySourceFactory::newSource(int offset) {
  ScopedLock l(lock_);
  if (duringShutdown_) {
    LOG(ERROR) << "Attempt to add a new source during shutdown";
    return NULL;
  }
  TrackSource* source = new TrackSource(this, offset);
  sources_->insert(source);
  return source;
}

BufferySourceFactory::~BufferySourceFactory() {
  while (true) {
    {
      ScopedLock l(lock_);
  while (!sources_.empty())
    sources_.begin()->clearFactory();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
