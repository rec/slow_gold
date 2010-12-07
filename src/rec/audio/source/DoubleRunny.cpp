#include "rec/audio/source/DoubleRunny.h"

namespace rec {
namespace audio {
namespace source {

DoubleRunny::~DoubleRunny() {
  trash::discard(runny_.transfer());
  trash::discard(nextRunny_.transfer());
}

Source* DoubleRunny::source() {
  ScopedLock l(lock_);
  return runny_;
}

void DoubleRunny::operator()(const slow::proto::Preferences& prefs) {
  const Track& track = prefs.track();
  if (track == prefs_.track())
    return;

  ratio_ = track.timestretch().time_scale() /
    prefs_.track().timestretch().time_scale();

  scoped_ptr<Runny> runny(newRunny(track));
  if (runny) {
    prefs_ = prefs;
    runny->setNextReadPosition(runny_ ? runny_->getNextReadPosition() : 0);
    Thread* thread = Thread::getCurrentThread();
    while (!(thread && thread->threadShouldExit()) && !runny->fill());
    runny->startThread();

    ScopedLock l(lock_);
    nextRunny_.swap(runny);
  }

  trash::discard(runny.transfer());
  trash::empty();
}

void DoubleRunny::getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
  scoped_ptr<Runny> lastRunny;
  {
    ScopedLock l(lock_);
    if (nextRunny_) {
      if (runny_)
        nextRunny_.setNextReadPosition(ratio_ * runny_.getNextReadPosition());

      lastRunny.swap(runny_);
      nextRunny_.swap(runny_);
    }
  }

  if (runny_)
    runny_->getNextAudioBlock(info);
  else
    LOG(ERROR) << "No runny";

  trash::discard(lastRunny.transfer());
}

}  // namespace source
}  // namespace audio
}  // namespace rec
