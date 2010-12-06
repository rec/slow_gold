#include "rec/audio/source/Runny.h"
#include "rec/audio/CopySamples.h"

namespace rec {
namespace audio {
namespace source {

Runny::Runny(const RunnyDesc& desc, Source* source)
    : Wrappy::Position(source),
      Thread("Runny"),
      buffer_(2, desc.buffer_size()),
      filled_(0, desc.buffer_size()),
      desc_(desc) {
  setPriority(desc.thread().priority());
}

Runny::~Runny() {}

void Runny::setNextReadPosition(int p) {
  {
    ScopedLock l(lock_);
    filled_.reset();
    position_ = p;
  }
  source_->setNextReadPosition(p);
}

bool Runny::fill() {
  AudioSourceChannelInfo info;
  {
    ScopedLock l(lock_);
    info.numSamples = juce::jmin(filled_.remainingBlock(),
                                 (int64)desc_.chunk_size());
    if (!info.numSamples)
      return true;  // No more to fill!

    info.startSample = filled_.end();
  }
  info.buffer = &buffer_;

  if (threadShouldExit())
    return true;

  source_->getNextAudioBlock(info);

  if (threadShouldExit())
    return true;

  ScopedLock l(lock_);
  return !filled_.fill(info.numSamples);
}

void Runny::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  int begin, ready;
  {
    ScopedLock l(lock_);
    begin = filled_.begin();
    ready = filled_.filled();
  }

  if (threadShouldExit())
    return;

  if (ready < info.numSamples)
    LOG(ERROR) << "Expected " << ready << " but got " << info.numSamples;
  copyCircularSamples(buffer_, begin, info);

  if (threadShouldExit())
    return;

  ScopedLock l(lock_);
  filled_.consume(info.numSamples);
}

void Runny::run() {
  while (!threadShouldExit()) {
    if (fill() && !threadShouldExit())
      wait(desc_.thread().period());
  }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
