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

static const int TEXT_WIDTH = 100;
static const int DIAL_WIDTH = 100;

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
    : Layout("Time controls", HORIZONTAL),
      songDial_(realTimeDial()),
      songTime_(Text()),
      timeScale_(1.0) {
  addToLayout(&songTime_, TEXT_WIDTH);
  addToLayout(&songDial_, DIAL_WIDTH);
  addToLayout(&filler_);
}

void TimeController::startListening() {
  songDial_.startListening();
}

void TimeController::operator()(const Stretch& stretch) {
  Lock l(lock_);
  timeScale_ = timeScale(stretch);
}

void TimeController::operator()(Samples<44100> time) {
  Samples<44100> scaledTime = time;
  if (DISPLAY_SCALED_TIME)
    scaledTime = static_cast<uint64>(scaledTime / timeScale_);
  songTime_(scaledTime);
  songDial_(scaledTime);
}

void TimeController::setLength(Samples<44100> len) {
  songTime_.setLength(len);
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
