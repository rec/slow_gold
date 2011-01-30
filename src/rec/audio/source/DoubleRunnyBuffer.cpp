#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/audio/source/StretchyRunny.h"
#include "rec/data/persist/Persist.h"
#include "rec/util/thread/Trash.h"

static const int COMPRESSION = 512;
static const int THREAD_TIMEOUT = 2000;
static const int SPIN_WAIT = 40;
static const int BLOCK_SIZE = 1024;
static const int READAHEAD = 20000;
static const int BUFFER_READAHEAD = 10000;

using namespace rec::gui;

namespace rec {
namespace audio {
namespace source {

DoubleRunnyBuffer::DoubleRunnyBuffer(const VirtualFile& file, Data* data,
                                     const RunnyProto& desc)
    : Thread("DoubleRunnyBuffer"), stretchy_(desc),
      runnyDesc_(desc), data_(data), empty_(false) {
  ptr<PositionableAudioSource> source(createSource(file));
  if (!source) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(file).toCString();
    empty_ = true;
    return;
  }

  File shadow = getShadowFile(file, "thumbnail.stream");
  int len = source->getTotalLength();
  cachedThumbnail_.reset(new CachedThumbnail(shadow, COMPRESSION, len));

  if (!cachedThumbnail_->isFull())
    source.reset(Snoopy::add(source.transfer(), cachedThumbnail_.get()));

  buffer_.reset(new FillableBuffer(source.transfer(), BLOCK_SIZE));

  StretchLoop loop(data_->get());
  setLoop(loop);

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
  setLoop(p);
}

bool DoubleRunnyBuffer::fillFromPosition(int pos) {
  buffer_->setPosition(pos);
  return buffer_->waitUntilFilled(block::Block(pos, pos + BUFFER_READAHEAD));
}

void DoubleRunnyBuffer::run() {
  while (!buffer_->isFull()) {
    if (threadShouldExit())
      return;
    else
      buffer_->fillNextBlock();
  }
  if (!threadShouldExit())
    cachedThumbnail_->writeThumbnail(true);
}

void DoubleRunnyBuffer::setLoop(const StretchLoop& loop) {
  if (threadShouldExit())
    return;

  startThread();
  int64 pos = stretchy_.getNextReadPosition();
  buffer_->waitUntilFilled(block::Block(pos, pos + READAHEAD));

  if (!threadShouldExit()) {
    ptr<BufferSource> s(new BufferSource(*buffer_->buffer()));
    stretchy_.setNextRunny(stretchyRunny(runnyDesc_, loop, pos, s.xfer()));
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
