#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/DoubleRunnyBuffer.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/audio/source/Snoopy.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/thread/Trash.h"

using namespace rec::gui;
using namespace rec::util::block;

namespace rec {
namespace audio {
namespace source {

DoubleRunnyBuffer::DoubleRunnyBuffer(const VirtualFile& file, Data* data,
                                     const RunnyProto& desc)
    : Thread("DoubleRunnyBuffer"),
      runnyDesc_(desc), data_(data), empty_(false) {
  ptr<PositionableAudioSource> source(createSource(file));
  if (!source) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(file).toCString();
    empty_ = true;
    return;
  }

  File shadow = getShadowFile(file, "thumbnail.stream");
  int len = source->getTotalLength();
  cachedThumbnail_.reset(new CachedThumbnail(shadow, desc.compression(), len));

  if (!cachedThumbnail_->isFull())
    source.reset(Snoopy::add(source.transfer(), cachedThumbnail_.get()));

  buffer_.reset(new FillableBuffer(source.transfer(), desc.chunk_size()));

  changeLocker_.reset(new ChangeLocker(desc.spin_wait()));
  changeLocker_->initialize(data_->get());
  data_->addListener(changeLocker_.get());

  changeLocker_->addListener(this);
  changeLocker_->startThread();
}

DoubleRunnyBuffer::~DoubleRunnyBuffer() {
  switching_.shutdown();
}

bool DoubleRunnyBuffer::waitUntilFilled(uint32 readahead) {
  int64 p = switching_.getNextReadPosition();
  return buffer_->waitUntilFilled(Block(p, p + readahead));
}

bool DoubleRunnyBuffer::fillFromPosition(int p) {
  // This is only called when the user clicks in the window to set a new
  // playback position.
  if (!buffer_)
    return false;

  buffer_->setPosition(p);
  return waitUntilFilled(runnyDesc_.buffer_readahead());
}

void DoubleRunnyBuffer::run() {
  while (!(buffer_->isFull() || threadShouldExit()))
    buffer_->fillNextBlock();

  if (!threadShouldExit())
    cachedThumbnail_->writeThumbnail(true);
}

void DoubleRunnyBuffer::operator()(const StretchLoop& loop) {
  if (threadShouldExit())
    return;

  {
    ScopedLock l(lock_);
#if 0
    if (loop == stretchLoop_) {
      DLOG(INFO) << "Duplicate StretchLoop seen";
      return;
    }
    DLOG(INFO) << "New loop " << loop.DebugString();
#endif

    stretchLoop_ = loop;
  }
  startThread();
  waitUntilFilled(runnyDesc_.readahead());

  if (!threadShouldExit()) {
    ptr<BufferSource> s(new BufferSource(*buffer_->buffer()));
    int64 p = switching_.getNextReadPosition();
    switching_.setNextRunny(stretchyRunny(runnyDesc_, loop, p, s.xfer()));
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
