#include "rec/audio/source/Runny.h"
#include "rec/audio/util/CopySamples.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

Runny::Runny(PositionableAudioSource* source, const RunnyProto& desc)
    : ThreadedSource(source, "Runny"),
      buffer_(2, desc.buffer_size()),
      filled_(desc.buffer_size()),
      desc_(desc) {
  setPriority(desc.thread().priority());
  DLOG(INFO) << "Runny: " << &buffer_;
}

Runny::~Runny() {}

void Runny::setNextReadPosition(int64 newPos) {
	// Not called during playback, only when jumping to a new location.
  {
    ScopedLock l(lock_);
    filled_.setBegin(newPos);
  }
  Wrappy::setNextReadPosition(newPos);
  notify();
}

void Runny::getNextAudioBlock(const AudioSourceChannelInfo& i) {
  AudioSourceChannelInfo info = i;
  int64 begin, ready;
  {
    ScopedLock l(lock_);
    begin = filled_.begin();
    ready = filled_.filled();
  }

  if (threadShouldExit())
    return;

  copyCircularSamples(buffer_, begin, info, ready);

  if (threadShouldExit())
    return;

  ScopedLock l(lock_);
  filled_.consume(i.numSamples);
  position_ = mod(position_ + i.numSamples);
#if 0
  LOG(INFO) << "position: " << position_
            << ", start:" << filled_.begin()
            << ", filled: " << filled_.filled() << "\n";
#endif
  notify();  // We get less of an interleave if we omit this!
}

void Runny::fillOnce() {
  if (threadShouldExit())
    return;

  AudioSourceChannelInfo info;
  {
    ScopedLock l(lock_);
    block::Block block = filled_.nextBlockToFill(desc_.chunk_size());
    info = block::audioSourceChannelInfo(block, &buffer_);
  }

  if (!info.numSamples || threadShouldExit())
    return;  // No more to fill!

  if (!prepared_)
    prepareToPlay(desc_.chunk_size(), 44100);

  if (!threadShouldExit())
    source()->getNextAudioBlock(info);

  if (!threadShouldExit()) {
    ScopedLock l(lock_);
    filled_.fill(info.numSamples);
  }

#if 0
  LOG(INFO) << "POSITION: " << position_
            << ", START:" << filled_.begin()
            << ", FILLED: " << filled_.filled() << "\n";
#endif
}

void Runny::run() {
  while (!(threadShouldExit())) {
    if (isFull())
      wait(desc_.thread().period());

    else
      fillOnce();
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
