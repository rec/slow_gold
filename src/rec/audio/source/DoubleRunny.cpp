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
}

Source* DoubleRunny::source() const {
  ScopedLock l(lock_);
  return runny_.get();
}

void DoubleRunny::setPreferences(const Preferences& prefs, int position, double ratio) {
  scoped_ptr<Runny> runny(filledRunny(prefs.track(), position));
  if (runny) {
    ScopedLock l(lock_);
    nextRunny_.swap(runny);
    ratio_ = ratio;
    if (!runny_)
      runny_.swap(nextRunny_);

    broadcast(this);
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
