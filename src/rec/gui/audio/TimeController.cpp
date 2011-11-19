#include "rec/gui/audio/TimeController.h"
#include "rec/audio/Audio.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/data/Data.h"
#include "rec/gui/Color.h"
#include "rec/gui/icon/MPStart.svg.h"
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

void TimeController::operator()(Samples<44100> time) {
  RealTime scaledTime = time;
  if (DISPLAY_SCALED_TIME)
    scaledTime /= timeScale_;
  songTime_(scaledTime);
  songDial_(scaledTime);
}

void TimeController::setLength(Samples<44100> len) {
  songTime_.setLength(len);
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
