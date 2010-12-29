#include "rec/audio/source/Runny.h"
#include "rec/audio/CopySamples.h"

using namespace juce;

namespace rec {
namespace audio {
namespace source {

Runny::Runny(Source* source, const RunnyProto& desc)
  : Thread("Runny"),
    Wrappy::Position(source),
    buffer_(2, desc.buffer_size()),
    filled_(desc.buffer_size()),
    desc_(desc) {
  setPriority(desc.thread().priority());
  DLOG(INFO) << "Creating runny " << this;
}

Runny::~Runny() {
  DLOG(INFO) << "Deleting runny with: " << this;
}

void Runny::setNextReadPosition(int newPos) {
  LOG_FIRST_N(INFO, 8) << "Setting next read position: " << newPos;

  {
    ScopedLock l(lock_);
    // Check if the new position is within the current readahead buffer.
    int available = filled_.availableFrom(newPos);
    filled_.reset(newPos);
    if (available >= 0)
      filled_.fill(available);
  }
  Wrappy::Position::setNextReadPosition(newPos);
  notify();
}

void Runny::getNextAudioBlock(const AudioSourceChannelInfo& i) {
  AudioSourceChannelInfo info = i;
  int begin, ready;
  {
    ScopedLock l(lock_);
    begin = filled_.begin();
    ready = filled_.filled();
    DLOG_EVERY_N(INFO, 64) << "-> * " << filled_.begin()
                           << ":" << filled_.filled() << ", " << this;
  }

  if (ready < info.numSamples) {
    LOG_FIRST_N(INFO, 1) << "LIMITED: request:" << info.numSamples
                         << " got:" << ready
                         << " filled: " << filled_.filled()
                         << " begin: " << filled_.begin();
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

bool Runny::fill() {
  if (threadShouldExit())
    return true;

  AudioSourceChannelInfo info;
  info.buffer = &buffer_;
  {
    ScopedLock l(lock_);
    info.startSample = filled_.end();
    info.numSamples = jmin(filled_.remainingBlock(), (int64)desc_.chunk_size());
  }

  if (!info.numSamples || threadShouldExit())
    return true;  // No more to fill!

  DLOG_EVERY_N(INFO, 64) << "* <- " << filled_.begin()
                         << ":" << filled_.filled() << ", " << this;

  source()->prepareToPlay(desc_.chunk_size(), 44100);

  if (threadShouldExit())
    return true;

  source()->getNextAudioBlock(info);

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
