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

Runny::~Runny() {}

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
      return true;  // No more to fill!

    info.buffer = &buffer_;
    info.startSample = filled_.end();
    info.numSamples = toFill;
  }

  source_->getNextAudioBlock(info);

  ScopedLock l(lock_);
  return !filled_.fill(toFill);
}

void Runny::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  int begin, ready;
  {
    ScopedLock l(lock_);
    begin = filled_.begin();
    ready = filled_.filled();
  }

  if (ready < info.numSamples)
    LOG(ERROR) << "Expected " << ready << " but got " << info.numSamples;

  copyCircularSamples(buffer_, begin, info);

  ScopedLock l(lock_);
  filled_.consume(info.numSamples);
}

class RunnyThread : public Thread {
 public:
  RunnyThread(Runny* runny, int wait)
      : Thread("RunnyThread"),
        runny_(runny),
        wait_(wait) {
  }

  virtual void run() {
    while (!threadShouldExit()) {
      if (!runny_->fill())
        wait(wait_);
    }
  }

 private:
  Runny* runny_;
  const int wait_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(RunnyThread);
};

Thread* Runny::makeThread(int wait) {
  return new RunnyThread(this, wait);
}

}  // namespace source
}  // namespace audio
}  // namespace rec
