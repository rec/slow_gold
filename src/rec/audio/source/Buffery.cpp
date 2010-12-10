#include <glog/logging.h>

#include "rec/audio/source/Buffery.h"
#include "rec/audio/CopySamples.h"
#include "rec/util/Math.h"
#include "rec/util/thread/Trash.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/MergeBlockSet.h"

using namespace rec::util::block;
using namespace rec::util::listener;
using namespace rec::util::thread;

#ifdef USE_MALLOC_FOR_BUFFERY
#  define BUFFER_SIZE 0
#else
#  define BUFFER_SIZE source->getTotalLength()
#endif

namespace rec {
namespace audio {
namespace source {

Buffery::Buffery(Source* source, int blockSize)
    : Thread("Buffery"),
      source_(source),
      buffer_(2, BUFFER_SIZE),
      isFull_(false),
      blockSize_(blockSize),
      position_(0) {
#ifdef USE_MALLOC_FOR_BUFFERY
  int len = getTotalLength();
  sampleData_[0] = (float*) malloc(sizeof(float) * len);
  sampleData_[1] = (float*) malloc(sizeof(float) * len);

  buffer_.setDataToReferTo(sampleData_, 2, len);
#endif
}

Buffery::~Buffery() {
#ifdef USE_MALLOC_FOR_BUFFERY
  free(sampleData_[0]);
  free(sampleData_[1]);
#endif
}

void Buffery::run() {
  while (!(threadShouldExit() || fillOnce()));
}

bool Buffery::isFull() const {
  ScopedLock l(lock_);
  return isFull_;
}

void Buffery::setReadPosition(int pos) {
  ScopedLock l(lock_);
  position_ = pos;
}

bool Buffery::fillFromSource(const Block& block) {
  ScopedLock l(lock_);
  if (isFull_) {
    LOG(ERROR) << "Calling fillFromSource when isFull_";
    return true;
  }

  if (!getSize(block)) {
    LOG(ERROR) << "Calling fillFromSource for no data.";
    return false;
  }

  AudioSourceChannelInfo info;
  info.buffer = &buffer_;
  info.startSample = block.first;
  info.numSamples = getSize(block);

  int length = getTotalLength();
  source_->setNextReadPosition(block.first);
  source_->getNextAudioBlock(info);
  position_ = util::mod(position_ + info.numSamples, length);
  Broadcaster<const AudioSourceChannelInfo&>::broadcast(info);

  merge(block, &filled_);
  isFull_ = isBlock(filled_, Block(0, length));
  if (isFull_)
    Broadcaster<const Buffery&>::broadcast(*this);

  return isFull_;
}

bool Buffery::fillBlock(const Block& block) {
  ScopedLock l(lock_);
  if (isFull_)
    return true;

  BlockSet blocks = difference(filled_, block);
  for (BlockSet::iterator i = blocks.begin(); i != blocks.end(); ++i) {
    if (fillFromSource(*i)) {
      if (++i != blocks.end())
        LOG(ERROR) << "Ran out of space with blocks to fill.";
      return true;
    }
  }
  return false;
}

bool Buffery::fillOnce() {
  ScopedLock l(lock_);
  return isFull_ ||
    fillFromSource(firstEmptyBlockAfter(filled_, position_, 
                                        getTotalLength()));
}

int Buffery::getAudioBlock(const AudioSourceChannelInfo& info, int position) {
  {
    ScopedLock l(lock_);
    if (!isFull_) {
      size_t end = position + info.numSamples;
      size_t length = getTotalLength();
      if (end <= length)
        fillBlock(Block(position, end));
      else
        fillBlock(Block(position, length)) || fillBlock(Block(0, end - length));

      position_ = end;
    }
  }

  return rec::audio::copyCircularSamples(buffer_, position, info);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
