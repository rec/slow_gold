#include <glog/logging.h>

#include "rec/audio/source/Runny.h"
#include "rec/audio/CopySamples.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

Runny::Runny(const RunnyDesc& desc, Source* source)
    : Wrappy(source),
      Thread("Runny"),
      buffer_(2, desc.buffer_size()),
      filled_(desc.buffer_size()),
      desc_(desc) {
  DLOG(INFO) << "Creating runny with: " << this << "\n" << desc.DebugString();
  setPriority(desc.thread().priority());
}

Runny::~Runny() {
  DLOG(INFO) << "Deleting runny with: " << this;
}

void Runny::setNextReadPosition(int newPos) {
  // DLOG(INFO) << "Setting next read position: " << newPos;
  {
    ScopedLock l(lock_);
    int64 skip = newPos - getNextReadPosition();

    if (skip >= 0 && skip <= filled_.filled())
      filled_.consume(skip);
    else
      filled_.reset();
  }

  notify();
  Wrappy::setNextReadPosition(newPos);
}

void Runny::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  int begin, ready;
  {
    ScopedLock l(lock_);
    begin = filled_.begin();
    ready = filled_.filled();
    // DLOG(INFO) << "-> * " << filled_.begin() << ":" << filled_.filled() << ", " << this;
  }

  if (threadShouldExit())
    return;

  if (ready < info.numSamples) {
    LOG_FIRST_N(ERROR, 9) << "request:" << info.numSamples << " got:" << ready;
  }

  copyCircularSamples(buffer_, begin, info);

  if (threadShouldExit())
    return;

  ScopedLock l(lock_);
  filled_.consume(info.numSamples);
}

bool Runny::fill() {
  AudioSourceChannelInfo info;
  {
    ScopedLock l(lock_);
    info.buffer = &buffer_;
    info.startSample = filled_.end();
    info.numSamples = jmin(filled_.remainingBlock(), (int64)desc_.chunk_size());
  }

  if (!info.numSamples || threadShouldExit())
    return true;  // No more to fill!

  // DLOG(INFO) << "* <- " << filled_.begin() << ":" << filled_.filled() << ", " << this;
  source_->getNextAudioBlock(info);

  if (threadShouldExit())
    return true;

  ScopedLock l(lock_);
  filled_.fill(info.numSamples);
  return !filled_.remaining();
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
