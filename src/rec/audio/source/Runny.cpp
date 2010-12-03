#include "rec/audio/source/Runny.h"
#include "rec/audio/CopySamples.h"

namespace rec {
namespace audio {
namespace source {

Runny::Runny(Source* source, int bufferSize, int minBufferSize, int chunkSize)
    : Wrappy::Position(source),
      buffer_(2, bufferSize),
      filled_(0, bufferSize),
      minBufferSize_(minBufferSize),
      chunkSize_(chunkSize) {
}

bool Runny::isReady() {
  ScopedLock l(lock_);
  return filled_.filled() >= minBufferSize_;
}

void Runny::setNextReadPosition(int p) {
  {
    ScopedLock l(lock_);
    filled_.reset();
    position_ = p;
  }
  source_->setNextReadPosition(p);
}

bool Runny::fill() {
  int toFill;
  AudioSourceChannelInfo info;
  {
    ScopedLock l(lock_);
    toFill = juce::jmin(filled_.remainingBlock(), (int64)chunkSize_);
    if (!toFill)
      return false;

    info.buffer = &buffer_;
    info.startSample = filled_.end();
    info.numSamples = toFill;
  }

  source_->getNextAudioBlock(info);

  ScopedLock l(lock_);
  return filled_.fill(toFill);
}

void Runny::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  ScopedLock l(lock_);
  int begin = filled_.begin();
  int ready = filled_.filled();

  {
    ScopedUnlock l(lock_);
    if (ready < info.numSamples)
      LOG(ERROR) << "Expected " << ready << " but got " << info.numSamples;

    copyCircularSamples(buffer_, begin, info);
  }

  filled_.consume(info.numSamples);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
