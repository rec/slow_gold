#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/Seggy.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/audio/source/StretchyRunny.h"
#include "rec/data/persist/Persist.h"
#include "rec/util/thread/Trash.h"

static const int COMPRESSION = 512;
static const int THREAD_TIMEOUT = 2000;
static const int SPIN_WAIT = 40;
static const int BLOCK_SIZE = 1024;
static const int READAHEAD = 20000;
static const int BUFFERY_READAHEAD = 10000;

using namespace rec::gui;

namespace rec {
namespace audio {
namespace source {

DoubleRunnyBuffer::DoubleRunnyBuffer(const VirtualFile& file, Data* data,
                                     const RunnyProto& desc)
    : Thread("DoubleRunnyBuffer"), stretchy_(file, desc),
      data_(data), empty_(false) {
  ptr<PositionableAudioSource> source(createSource(file));
  if (!source) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(file).toCString();
    empty_ = true;
    return;
  }

  int len = source->getTotalLength();
  File shadow = getShadowFile(file, "thumbnail.stream");
  cachedThumbnail_.reset(new CachedThumbnail(shadow, COMPRESSION, len));

  if (!cachedThumbnail_->isFull())
    source.reset(Snoopy::add(source.transfer(), cachedThumbnail_.get()));

  source.reset(new Seggy(SampleRange(0, len), source.transfer()));
  buffery_.reset(new FillableBuffer(source.transfer(), BLOCK_SIZE));

  StretchLoop loop(data_->get());
  setLoop(loop, stretchy_.setLoopPosition(loop));

  changeLocker_.reset(new ChangeLocker(SPIN_WAIT));
  changeLocker_->initialize(data_->get());
  data_->addListener(changeLocker_.get());
  changeLocker_->addListener(this);
  changeLocker_->startThread();
}

DoubleRunnyBuffer::~DoubleRunnyBuffer() {
  stretchy_.shutdown();
}

void DoubleRunnyBuffer::operator()(const StretchLoop& p) {
  setLoop(p, stretchy_.setLoopPosition(p));
}

PositionableAudioSource* DoubleRunnyBuffer::makeSource() {
  if (threadShouldExit())
    return NULL;

  startThread();
  int64 pos = stretchy_.getNextReadPosition();
  buffery_->waitUntilFilled(block::Block(pos, pos + READAHEAD));
  return new BufferSource(*buffery_->buffer());
}

bool DoubleRunnyBuffer::fillFromPosition(int pos) {
  buffery_->setPosition(pos);
  return buffery_->waitUntilFilled(block::Block(pos, pos + BUFFERY_READAHEAD));
}

void DoubleRunnyBuffer::run() {
  while (!buffery_->isFull()) {
    if (threadShouldExit())
      return;
    else
      buffery_->fillNextBlock();
  }
  if (!threadShouldExit()) {
    cachedThumbnail_->writeThumbnail(true);
  }
}

void DoubleRunnyBuffer::setLoop(const StretchLoop& loop, int pos) {
  ptr<PositionableAudioSource> source(makeSource());
  if (!source) {
    LOG(ERROR) << "Couldn't make source";
    return;
  }

  ptr<Runny> runny(makeStretchyRunny(RunnyProto(), loop.stretchy(),
                                     pos, source.transfer()));
  if (runny)
    stretchy_.setNext(runny.transfer());
}

}  // namespace source
}  // namespace audio
}  // namespace rec
