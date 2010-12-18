#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/widget/tree/VolumeFile.h"

static const int COMPRESSION = 512;

namespace rec {
namespace audio {
namespace source {

DoubleRunnyBuffer::DoubleRunnyBuffer(const VolumeFile& file, int blockSize)
    : Thread("DoubleRunnyBuffer"),
      buffery_(Snoopy::add(createSource(file), &cachedThumbnail_), blockSize),
      cachedThumbnail_(getShadowFile(file, "thumbnail.stream"),
                       COMPRESSION, buffery_.getLength()) {
  buffery_.addListener(this);
}

PositionableAudioSource* DoubleRunnyBuffer::makeSource(const VolumeFile& f) {
  for (int i = 0; !buffery_.hasFilled(READAHEAD); ++i) {
    if ((i * WAIT_TIME) > MAX_WAIT_TIME) {
      LOG(ERROR) << "Waited for a long time, no data: " << i * WAIT_TIME;
      return NULL;
    }
    wait(WAIT_TIME);
  }

  return new BufferySource(*buffery_.buffer());
}

void DoubleRunnyBuffer::run() {
  DLOG(INFO) << "Starting to fetch.";
  while (!(threadShouldExit() || buffery_.isFull()))
    buffery_.fillNextBlock();
  DLOG_IF(INFO, buffery_.isFull()) << "buffer is full";
}

  void DoubleRunnyBuffer::operator()(const Buffery&) {
  cachedThumbnail_.writeThumbnail(true);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
