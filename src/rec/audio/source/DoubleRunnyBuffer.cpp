#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/data/persist/Persist.h"
#include "rec/util/thread/Trash.h"

static const int COMPRESSION = 512;
static const int THREAD_TIMEOUT = 2000;
static const int SPIN_WAIT = 40;
static const int BLOCK_SIZE = 1024;

namespace rec {
namespace audio {
namespace source {

static const int READAHEAD = 20000;


DoubleRunnyBuffer::DoubleRunnyBuffer(const VolumeFile& file, Data* data)
    : DoubleRunny(file), Thread("DoubleRunnyBuffer"),
      data_(data), empty_(false) {
  ptr<PositionableAudioSource> source(createSource(file));
  if (!source) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(file).toCString();
    empty_ = true;
    return;
  }

  File shadowThumbnailFile = getShadowFile(file, "thumbnail.stream");
  cachedThumbnail_.reset(new CachedThumbnail(shadowThumbnailFile, COMPRESSION,
                                             source->getTotalLength()));

  if (!cachedThumbnail_->isFull())
    source.reset(Snoopy::add(source.transfer(), cachedThumbnail_.get()));
  buffery_.reset(new Buffery(source.transfer(), BLOCK_SIZE));

  setStretchy(data_->get());
  changeLocker_.reset(new ChangeLocker(SPIN_WAIT));
  changeLocker_->initialize(data->get());
  changeLocker_->addListener(this);
  changeLocker_->startThread();
  data_->addListener(changeLocker_.get());
}

DoubleRunnyBuffer::~DoubleRunnyBuffer() {}

PositionableAudioSource* DoubleRunnyBuffer::makeSource() {
  if (threadShouldExit())
    return NULL;

  startThread();
  int pos = getNextReadPosition();
  buffery_->waitUntilFilled(block::Block(pos, pos + READAHEAD));
  return new BufferSource(*buffery_->buffer());
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
  return buffery_->waitUntilFilled(block::Block(pos, pos + BUFFERY_READAHEAD));
}

void DoubleRunnyBuffer::run() {
  DLOG(INFO) << "DoubleRunnyBuffer::run";
  while (!buffery_->isFull()) {
    if (threadShouldExit())
      return;
    else
      buffery_->fillNextBlock();
  }
  if (!threadShouldExit()) {
    cachedThumbnail_->writeThumbnail(true);
    DLOG(INFO) << "run(): buffery_.isFull()";
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
