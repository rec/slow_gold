#include "rec/audio/source/BufferySourceFactory.h"
#include "rec/audio/source/TrackSource.h"
#include "rec/widget/tree/VolumeFile.h"

using namespace rec::widget::tree;

namespace rec {
namespace audio {
namespace source {

BufferySourceFactory::BufferySourceFactory(const VolumeFile& f, int blockSize)
    : Buffery(new AudioFormatReaderSource(createReader(f), true), blockSize), duringShutdown_(false) {
}

Source* BufferySourceFactory::newSource(int offset) {
  ScopedLock l(lock_);
  if (duringShutdown_) {
    LOG(ERROR) << "Attempt to add a new source during shutdown";
    return NULL;
  }
  TrackSource* source = new TrackSource(this, offset);
  sources_.insert(source);
  return source;
}

BufferySourceFactory::~BufferySourceFactory() {
  ScopedLock l(lock_);
  while (!sources_.empty())
    (*sources_.begin())->release();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
