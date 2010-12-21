#include "rec/audio/source/Buffery.h"
#include "rec/audio/CopySamples.h"
#include "rec/util/Math.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/MergeBlockSet.h"

using namespace rec::util::block;
using namespace rec::util::listener;

namespace rec {
namespace audio {
namespace source {

Buffery::Buffery(PositionableAudioSource* source, int blockSize)
    : length_(source->getTotalLength()),
      buffer_(2, length_),
      position_(0),
      source_(source),
      blockSize_(blockSize) {
}

void Buffery::setPosition(int position) {
  ScopedLock l(lock_);
  position_ = position;
}

bool Buffery::hasFilled(int length) const {
  ScopedLock l(lock_);
  return hasFilled(Block(position_, position_ + length));
}

bool Buffery::hasFilled(const Block& b) const {
  ScopedLock l(lock_);
  if (isFull())
    return true;

  if (b.second <= length_)
    return difference(filled_, b).empty();

  return hasFilled(Block(b.first, length_)) &&
    hasFilled(Block(0, b.second - length_));
}

bool Buffery::isFull() const {
  ScopedLock l(lock_);
  return (fullTo(filled_) == length_);
}

void Buffery::fillNextBlock() {
  Block block;
  {
    ScopedLock l(lock_);
    block = firstEmptyBlockAfter(filled_, position_, length_);
  }

  int numSamples = getSize(block);
  if (!numSamples) {
    LOG(ERROR) << "Getting an empty block";
    return;
  }

  AudioSourceChannelInfo info;
  info.buffer = &buffer_;
  info.startSample = block.first;
  info.numSamples = juce::jmin(numSamples, blockSize_);
  block.second = block.first + info.numSamples;

  source_->setNextReadPosition(block.first);
  source_->getNextAudioBlock(info);

  bool full;
  {
    ScopedLock l(lock_);
    merge(block, &filled_);
    full = isFull();
  }
  if (full)
    broadcast(*this);
}

bool Buffery::waitUntilFilled(int length, int waitTime, int maxTime) {
  Thread* thread = Thread::getCurrentThread();
  for (int time = 0; !thread->threadShouldExit(); time += waitTime) {
    if (hasFilled(length))
      return true;

    if (time > maxTime) {
      LOG(ERROR) << "Waited for a long time, no data: " << time;
      return false;
    }
    thread->wait(waitTime);
  }
  return false;
}

}  // namespace source
}  // namespace audio
}  // namespace rec
