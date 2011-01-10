#include "rec/slow/app/TimeController.h"
#include "rec/data/persist/Persist.h"
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

TimeController::TimeController()
    : Layout("Time controls", VERTICAL),
      transportLayout_("Transport"),
      timesAndClockLayout_("Times and clock"),
      timesLayout_("Times", VERTICAL),
      transportSource_(NULL),
      startStopButton_("Start stop button", juce::DrawableButton::ImageFitted),
      songTime_(Text()),
      songDial_(realTimeDial()),
      time_(0.0),
      length_(0.0) {
  startStopButton_.setImages(gui::icon::MediaPlaybackStart::get(),
                             NULL, NULL, NULL,
                             gui::icon::MediaPlaybackStop::get());
  startStopButton_.setClickingTogglesState(true);
  startStopButton_.addListener(this);
  addListener(&songDial_);
  addListener(&realTime_);
  addListener(&songTime_);

  transportLayout_.addToLayout(&startStopButton_, 30);
  timesAndClockLayout_.addToLayout(&timesLayout_, 100);
  timesAndClockLayout_.addToLayout(&songDial_, 20, -1.0, -1.0);

  addToLayout(&transportLayout_, 30);
  addToLayout(&timesAndClockLayout_, -1.0);

  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(&songTime_);
  addAndMakeVisible(&songDial_);
}

void TimeController::setTransport(AudioTransportSourcePlayer* source) {
  if (transportSource_)
    transportSource_->removeListener(this);

  transportSource_ = source;

  if (transportSource_)
    transportSource_->addListener(this);
}

void TimeController::buttonClicked(juce::Button *button) {
  if (button == &startStopButton_)
    transportSource_->toggle();
}

void TimeController::setTimeOrLength(float time, float length) {
  ClockUpdate update;
  {
    ScopedLock l(lock_);
    if (time >= 0.0)
      time_ = time;
    if (length >= 0.0)
      length_ = length;
    update = ClockUpdate(time_, length_);
  }
  broadcast(update);
}

void TimeController::setLength(int length) {
  setTimeOrLength(-1, length / 44100.0);
}

void TimeController::operator()(float time) {
  setTimeOrLength(time, -1);
}

void TimeController::operator()(const AudioTransportSourcePlayer& player) {
  thread::callAsync(this, &TimeController::setButtonState);
}

void TimeController::setButtonState() {
  startStopButton_.setToggleState(transportSource_->isPlaying(), false);
  startStopButton_.repaint();
}

}  // namespace slow
}  // namespace rec
