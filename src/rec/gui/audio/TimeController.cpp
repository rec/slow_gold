#include "rec/gui/audio/TimeController.h"
#include "rec/audio/Audio.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Color.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/music/Metadata.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

using namespace juce;
using namespace rec::widget::status::time;
using namespace rec::audio::stretch;

namespace {

Dial realTimeDial() {
  Dial dial;
  gui::Colors* colors = dial.mutable_widget()->mutable_colors();
  colors->add_color()->set_argb(Colours::white.getARGB());
  colors->add_color()->set_argb(Colours::green.getARGB());
  colors->add_color()->set_argb(Colours::red.getARGB());

  return dial;
}

}  // namespace

TimeController::TimeController()
    : Layout("Time controls", VERTICAL),
      songDial_(realTimeDial()),
      songTime_(Text()),
      timeScale_(1.0),
      timesLayout_("Times", HORIZONTAL) {
  addToLayout(&timesLayout_);
  addToLayout(&songDial_);
  timesLayout_.addToLayout(&songTime_);
}

void TimeController::operator()(const Stretch& stretch) {
  ScopedLock l(lock_);
  timeScale_ = timeScale(stretch);
}

void TimeController::operator()(const Range<RealTime>& r) {
  songDial_(r);
}

void TimeController::operator()(SamplePosition time) {
  RealTime scaledTime = RealTime(time) / timeScale_;
  songTime_(scaledTime);
  songDial_(scaledTime);
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
