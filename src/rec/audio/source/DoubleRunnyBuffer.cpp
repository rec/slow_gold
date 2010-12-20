#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/widget/tree/VolumeFile.h"

static const int COMPRESSION = 512;
static const int THREAD_TIMEOUT = 2000;

namespace rec {
namespace audio {
namespace source {

DoubleRunnyBuffer::DoubleRunnyBuffer(const VolumeFile& file, int blockSize)
    : Thread("DoubleRunnyBuffer") {
  PositionableAudioSource* source = createSource(file);
  File shadowFile = getShadowFile(file, "thumbnail.stream");
  cachedThumbnail_.reset(new CachedThumbnail(shadowFile, COMPRESSION,
                                             source->getTotalLength()));
  if (!cachedThumbnail_->isFull())
    source = Snoopy::add(source, cachedThumbnail_.get());
  buffery_.reset(new Buffery(source, blockSize));
  buffery_->addListener(this);
}

PositionableAudioSource* DoubleRunnyBuffer::makeSource(const VolumeFile& f) {
  if (threadShouldExit())
    return NULL;

  startThread();
  for (int i = 0; !buffery_->hasFilled(READAHEAD); ++i) {
    if (threadShouldExit())
      return NULL;

    if (buffery_->isFull()) {
      LOG(ERROR) << "Full but not hasFilled?";
      break;
    }

    if ((i * WAIT_TIME) > MAX_WAIT_TIME) {
      LOG(ERROR) << "Waited for a long time, no data: " << i * WAIT_TIME;
      return NULL;
    }
    wait(WAIT_TIME);
  }

  return new BufferySource(*buffery_->buffer());
}

void DoubleRunnyBuffer::run() {
  DLOG(INFO) << "DoubleRunnyBuffer::run";
  while (!(threadShouldExit() || buffery_->isFull())) {
    buffery_->fillNextBlock();
  }
  DLOG_IF(INFO, buffery_->isFull()) << "DoubleRunnyBuffer::run: isFull";
}

void DoubleRunnyBuffer::operator()(const Buffery&) {
  cachedThumbnail_->writeThumbnail(true);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
