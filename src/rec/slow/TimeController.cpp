#include "rec/slow/TimeController.h"
#include "rec/data/persist/Persist.h"
#include "rec/audio/stretch/Stretchy.h"
#include "rec/gui/StretchyController.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/Color.h"
#include "rec/slow/AudioTransportSourcePlayer.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/cd/Album.h"

namespace rec {
namespace slow {

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

TimeController::TimeController(AudioTransportSourcePlayer* ts)
    : Layout("Time controls", VERTICAL),
      transportSource_(ts),
      timesLayout_("Times", HORIZONTAL),
      songDial_(realTimeDial()),
      realTime_("Real", Text()),
      songTime_("Track", Text()) {
  addListener(&songDial_);
  addListener(&realTime_);
  addListener(&songTime_);

  addToLayout(&timesLayout_);
  addToLayout(&songDial_);
  timesLayout_.addToLayout(&realTime_);
  timesLayout_.addToLayout(&songTime_);
}

void TimeController::operator()(const StretchLoop& stretchy) {
  songTime_.setTimeScale(1.0 / timeScale(stretchy.stretchy()));
}

void TimeController::operator()(const SelectionRange& r) {
  realTime_(r);
  songTime_(r);
}

}  // namespace slow
}  // namespace rec
