#include "rec/slow/app/TimeController.h"
#include "rec/data/persist/Persist.h"
#include "rec/audio/source/Stretchy.h"
#include "rec/gui/StretchyController.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/Color.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/cd/Album.h"

using namespace rec::proto::arg;

using juce::Colours;
using rec::gui::Colors;
using rec::widget::status::time::Dial;
using rec::widget::status::time::DialComponent;
using rec::widget::status::time::Text;
using rec::widget::status::time::TextComponent;

namespace rec {
namespace slow {

namespace {

Dial realTimeDial() {
  Dial dial;
  Colors* colors = dial.mutable_widget()->mutable_colors();
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

void TimeController::operator()(const audio::source::StretchyProto& stretchy) {
  songTime_.setTimeScale(1.0 / timeScale(stretchy));
}

}  // namespace slow
}  // namespace rec
