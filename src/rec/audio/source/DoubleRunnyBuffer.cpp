#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/util/thread/Trash.h"
#include "rec/util/thread/ChangeLocker.h"

static const int COMPRESSION = 512;
static const int THREAD_TIMEOUT = 2000;
static const int SPIN_WAIT = 40;
static const int BLOCK_SIZE = 1024;

namespace rec {
namespace audio {
namespace source {

static const int READAHEAD = 20000;
static const int WAIT_TIME = 20;
static const int MAX_WAIT_TIME = 7000;

DoubleRunnyBuffer::DoubleRunnyBuffer(const VolumeFile& file, Data* data)
    : DoubleRunny(file), Thread("DoubleRunnyBuffer"), data_(data) {
  ptr<PositionableAudioSource> source(createSource(file));

  File shadowThumbnailFile = getShadowFile(file, "thumbnail.stream");
  cachedThumbnail_.reset(new CachedThumbnail(shadowThumbnailFile, COMPRESSION,
                                             source->getTotalLength()));

  if (!cachedThumbnail_->isFull())
    source.reset(Snoopy::add(source.transfer(), cachedThumbnail_.get()));
  buffery_.reset(new Buffery(source.transfer(), BLOCK_SIZE));

  setStretchy(data_->get());
  buffery_->addListener(this);
  changeLocker_.reset(new ChangeLocker(SPIN_WAIT));
  changeLocker_->initialize(data->get());
  changeLocker_->addListener(this);
  changeLocker_->startThread();
  data_->addListener(changeLocker_.get());
}

PositionableAudioSource* DoubleRunnyBuffer::makeSource(const VolumeFile& f) {
  if (threadShouldExit())
    return NULL;

  startThread();
  buffery_->waitUntilFilled(READAHEAD);
  return new BufferySource(*buffery_->buffer());
}

void DoubleRunnyBuffer::operator()(const StretchyProto& p) {
  if (changeLocker_)
    changeLocker_->set(p);
  else
    LOG(ERROR) << "Empty changelocker";
}

static const int BUFFERY_READAHEAD = 10000;

bool DoubleRunnyBuffer::fillFromPosition(int pos) {
  buffery_->setPosition(pos);
  return buffery_->waitUntilFilled(BUFFERY_READAHEAD);
}

void DoubleRunnyBuffer::run() {
  DLOG(INFO) << "DoubleRunnyBuffer::run";
  while (!(threadShouldExit() || buffery_->isFull()))
    buffery_->fillNextBlock();

  DLOG_IF(INFO, buffery_->isFull()) << "DoubleRunnyBuffer::run: isFull";
}

void DoubleRunnyBuffer::operator()(const Buffery&) {
  cachedThumbnail_->writeThumbnail(true);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
