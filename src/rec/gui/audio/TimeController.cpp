#include "rec/gui/audio/TimeController.h"
#include "rec/audio/Audio.h"
#include "rec/audio/stretch/Stretch.h"
#include "rec/data/Data.h"
#include "rec/gui/Color.h"
#include "rec/music/Metadata.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

// Skin

static const int TEXT_WIDTH = 100;
static const int DIAL_WIDTH = 45;

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
    : Panel("Time controls", HORIZONTAL),
      songDial_(realTimeDial()),
      songTime_(Text()) {
  addToPanel(&songTime_, TEXT_WIDTH);
  addToPanel(&songDial_, DIAL_WIDTH);
  addToPanel(&filler_);
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
