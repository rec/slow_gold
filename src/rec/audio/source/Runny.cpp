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
}

Runny::~Runny() {}

void Runny::setNextReadPosition(int64 newPos) {
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

  if (ready < info.numSamples) {
    LOG(ERROR) << "clearing " << info.numSamples - ready
               << ", getting " << ready;

    info.buffer->clear(info.startSample + ready, info.numSamples - ready);
    info.numSamples = ready;
  }

  if (threadShouldExit())
    return;

  copyCircularSamples(buffer_, begin, info);

  if (threadShouldExit())
    return;

  ScopedLock l(lock_);
  filled_.consume(i.numSamples);
  position_ = mod(position_ + i.numSamples);
}

void Runny::fillOnce() {
  if (threadShouldExit())
    return;

  AudioSourceChannelInfo info;
  info.buffer = &buffer_;
  {
    ScopedLock l(lock_);
    info.startSample = filled_.end();
    info.numSamples = jmin(filled_.remainingBlock(), (int64)desc_.chunk_size());
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
