#include "rec/gui/audio/TimeController.h"
#include "rec/data/persist/Persist.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/gui/audio/StretchyController.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/Color.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/cd/Album.h"

namespace rec {
namespace gui {
namespace audio {

using namespace juce;
using namespace rec::proto::arg;
using namespace rec::widget::status::time;

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
      timesLayout_("Times", HORIZONTAL),
      songDial_(realTimeDial()),
      songTime_("Track", Text()),
      timeScale_(1.0) {
  addListener(&songDial_);
  addListener(&songTime_);

  addToLayout(&timesLayout_);
  addToLayout(&songDial_);
  timesLayout_.addToLayout(&songTime_);
}

void TimeController::operator()(const StretchLoop& stretchLoop) {
  ScopedLock l(lock_);
  timeScale_ = timeScale(stretchLoop.stretch());
}

void TimeController::operator()(const Range<RealTime>& r) {
  songDial_(r);
}

void TimeController::operator()(RealTime time) {
  RealTime scaledTime = time / timeScale_;
  songTime_(scaledTime);
  songDial_(scaledTime);
}

