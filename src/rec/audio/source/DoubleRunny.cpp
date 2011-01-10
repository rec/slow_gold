#include "rec/audio/source/DoubleRunny.h"
#include "rec/audio/source/Clear.h"
#include "rec/audio/source/Runny.h"

namespace rec {
namespace audio {
namespace source {

DoubleRunny::DoubleRunny(const RunnyProto& d)
    : Wrappy::Position(NULL), runnyDesc_(d) {
}

DoubleRunny::~DoubleRunny() {}

void DoubleRunny::set(Runny* next) {
  thread_ptr<Runny> runny(next);
  {
    ScopedLock l(lock_);
    nextRunny_.swap(runny);
  }
}

void DoubleRunny::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  thread_ptr<Runny> deleter;
  {
    ScopedLock l(lock_);
    if (nextRunny_) {
      prepareNext(nextRunny_.get());
      nextRunny_.swap(runny_);
      deleter.swap(nextRunny_);
    }
  }

  if (runny_)
    runny_->getNextAudioBlock(info);
  else
    clear(info);

  position_ = mod(position_ + info.numSamples);
}

PositionableAudioSource* DoubleRunny::getSource() const { return runny_.get(); }

void DoubleRunny::shutdown() {
  runny_.reset();
  nextRunny_.reset();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
