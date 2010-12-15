#include "rec/audio/source/DoubleRunny.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/Panes.h"
#include "rec/audio/source/StretchyFactory.h"

using namespace rec::util::thread;
using namespace rec::slow::proto;
using rec::widget::pane::Track;

namespace rec {
namespace audio {
namespace source {

DoubleRunny::~DoubleRunny() {
  trash::discard(runny_.transfer());
  trash::discard(nextRunny_.transfer());
  trash::empty();
}

Source* DoubleRunny::source() const {
  ScopedLock l(lock_);
  return runny_.get();
}

PositionableAudioSource* DoubleRunny::makeSource(const VolumeFile& f) {
  scoped_ptr<AudioFormatReader> r(createReader(file));
  return r ? new AudioFormatReaderSource(r.transfer(), true) : NULL;
}

void DoubleRunny::setPreferences(const Preferences& prefs,
                                 int position, double ratio) {
  setPosition(position);
  scoped_ptr<PositionableAudioSource> src(makeSource(prefs.track().file()));
  if (!src)
    return;

  scoped_ptr<Stretchy> str(new Stretchy(prefs.timestretch(), src.transfer()));
  scoped_ptr<Runny> runny(new Runny(prefs.runny(), str.transfer()));

  runny->setNextReadPosition(position);
  while (!(threadShouldExit() || runny->fill()));
  runny->startThread();

  {
    ScopedLock l(lock_);
    nextRunny_.swap(runny);
    ratio_ = ratio;
    if (!runny_)
      runny_.swap(nextRunny_);
  }

  broadcast(this);
  trash::discardAndEmpty(runny.transfer());
}

void DoubleRunny::getNextAudioBlock(const juce::AudioSourceChannelInfo& info) {
  scoped_ptr<Runny> lastRunny;
  {
    ScopedLock l(lock_);
    if (nextRunny_) {
      if (runny_)
        nextRunny_->setNextReadPosition(ratio_ * runny_->getNextReadPosition());

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
