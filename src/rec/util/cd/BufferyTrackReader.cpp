#include "rec/util/cd/BufferyTrackReader.h"

namespace rec {
namespace util {
namespace cd {

BufferyTrackReader::BufferyTrackReader() {}
BufferyTrackReader::~BufferyTrackReader() {
  trash::discard(buffery_->transfer());
}

AudioFormatReader* BufferyTrackReader::getTrackReader(const VolumeFile& file) {
  ScopedLock l(lock_);
  if (file != file_)
    setNewFile(file);

  return new TrackReader(this);
}


private:
void setNewFile(const VolumeFile& file) {
  file_ = file;
}

AudioFormatReader* createTrackReader() const {

}

}  // namespace cd
}  // namespace util
}  // namespace rec
