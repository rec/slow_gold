#include "rec/slow/app/MainPageController.h"
#include "rec/gui/StretchyController.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/Color.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/util/thread/CallAsync.h"

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


MainPageController::MainPageController(AudioTransportSourcePlayer* transport)
    : Layout(VERTICAL, true, "Main controls"),
      transportSource_(transport),
      startStopButton_("Start stop button", juce::DrawableButton::ImageFitted),
      disableButton_("Disable pitch/time shift", Address("disabled")),
      songTime_(Text()),
      songDial_(realTimeDial()) {
  startStopButton_.setImages(gui::icon::MediaPlaybackStart::get(),
                             NULL, NULL, NULL,
                             gui::icon::MediaPlaybackStop::get());
  startStopButton_.setClickingTogglesState(true);
  addAndMakeVisible(&disableButton_);
  addAndMakeVisible(&startStopButton_);
  addAndMakeVisible(&stretchyController_);

  addAndMakeVisible(&songTime_);
  addAndMakeVisible(&songDial_);

  startStopButton_.addListener(this);
  disableButton_.addListener(this);

  transportSource_->addListener(&songDial_);
  transportSource_->addListener(&songTime_);
  transportSource_->changeBroadcaster()->addListener(this);
}

void MainPageController::operator()(float time) {
  if (data())
    broadcast(time / data()->get().time_scale());
}

void MainPageController::operator()(const StretchyProto& desc) {
  thread::callAsync(&stretchyController_, &Component::setEnabled,
                    !desc.disabled());
}

void MainPageController::buttonClicked(juce::Button *button) {
  if (button == &startStopButton_)
    transportSource_->toggle();

  else if (button == &disableButton_ && data())
    data()->set("disable", disableButton_.getToggleState());
}

void MainPageController::setLength(int length) {
  songDial_.setLength(length);
}

void MainPageController::operator()(const AudioTransportSourcePlayer& player) {
  thread::callAsync(this, &MainPageController::setButtonState);
}

void MainPageController::setButtonState() {
  startStopButton_.setToggleState(transportSource_->isPlaying(), false);
  startStopButton_.repaint();
}

void MainPageController::setData(Data* data) {
  DataListener<StretchyProto>::setData(data);
  disableButton_.setData(data);
  stretchyController_.setData(data);
  bool enable = !(data && data->get().disabled());

  if (enable != stretchyController_.isEnabled())
    thread::callAsync(&stretchyController_, &Component::setEnabled, enable);

}

void MainPageController::resized() {
  startStopButton_.setBounds(16, 10, 42, 42);
  disableButton_.setBounds(16, 70, 150, 20);
  stretchyController_.setBounds(200, 0, getWidth() - 250, 85);

  songTime_.setBounds(getWidth() - 120, 60, 110, 22);
  songDial_.setBounds(getWidth() - 46, 90 - 46, 36, 36);
}

}  // namespace slow
}  // namespace rec
