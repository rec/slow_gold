#include "rec/audio/source/Switching.h"
#include "rec/audio/util/Clear.h"
#include "rec/audio/source/Runny.h"

namespace rec {
namespace audio {
namespace source {

Switching::Switching() : Wrappy(NULL) {}
Switching::~Switching() {}

void Switching::setNextRunny(ThreadedSource* next) {
  thread_ptr<ThreadedSource> runny(next);
  {
    ScopedLock l(lock_);
    nextRunny_.swap(runny);
  }
}

void Switching::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  thread_ptr<ThreadedSource> deleter;
  ScopedLock l(lock_);

  if (nextRunny_) {
    VLOG(1) << "Switching to next player";
    nextRunny_.swap(runny_);
    deleter.swap(nextRunny_);
  }

  if (runny_) {
    runny_->getNextAudioBlock(info);
  } else {
    LOG(ERROR) << "No runny in Switching";
    clear(info);
  }

  position_ = mod(position_ + info.numSamples);
}

void Switching::shutdown() {
  ScopedLock l(lock_);

  runny_.reset();
  nextRunny_.reset();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
