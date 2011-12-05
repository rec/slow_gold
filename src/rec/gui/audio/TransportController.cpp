#include "rec/gui/audio/TransportController.h"

#include "rec/command/CommandIDEncoder.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/icon/MPStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/icon/ZoomIn.svg.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

namespace {

const int ICON_SIZE = 40;
const int SLIDER_HEIGHT = 18;
const int MUTE_BUTTON_SIZE = 50;

const char* const MUTE_BUTTON_TEXT = "Mute";

}  // namespace

TransportController::TransportController(TimeController* timeController)
    : Layout("TransportController", VERTICAL),
      timeController_(timeController),
      buttonsLayout_("Buttons", HORIZONTAL),
      gainLayout_("Gain", HORIZONTAL),
      startStopButton_("Start/stop", juce::DrawableButton::ImageFitted),
      jumpToStartButton_("Jump to start", juce::DrawableButton::ImageFitted),
      level_("Gain", data::Address("gain")),
      muteButton_(MUTE_BUTTON_TEXT, data::Address("mute")) {
  startStopButton_.setClickingTogglesState(true);

  jumpToStartButton_.setImages(ptr<Drawable>(icon::ZoomIn::create()).get());
  startStopButton_.setImages(
      ptr<Drawable>(icon::MediaPlaybackStart::create()).get(),
      NULL, NULL, NULL,
      ptr<Drawable>(icon::MediaPlaybackStop::create()).get());

  jumpToStartButton_.addListener(this);
  startStopButton_.addListener(this);

  buttonsLayout_.addToLayout(&startStopButton_, ICON_SIZE);
  buttonsLayout_.addToLayout(&jumpToStartButton_, ICON_SIZE);
  buttonsLayout_.addToLayout(timeController_);

  level_.slider()->setRange(-36.0, +12.0, 0.1);
  level_.slider()->setDetent(0.0f);
  level_.slider()->setTextValueSuffix(" dB");

  gainLayout_.addToLayout(&level_);
  gainLayout_.addToLayout(&muteButton_, MUTE_BUTTON_SIZE);

  addToLayout(&buttonsLayout_, 40);
  addToLayout(&gainLayout_, 40);
  addToLayout(&levelMeter_);
}

TransportController::~TransportController() {}

using rec::audio::transport::State;

void TransportController::operator()(State state) {
  thread::callAsync(this, &TransportController::setTransportState, state);
}

void TransportController::buttonClicked(juce::Button *button) {
  using namespace rec::command;
  static CommandID JUMP_TO_FIRST_SELECTED =
    CommandIDEncoder::toCommandID(CommandIDEncoder::FIRST,
                                  Command::JUMP_SELECTED);

  if (button == &startStopButton_)
    broadcast(Command::TOGGLE_START_STOP);

  else if (button == &jumpToStartButton_)
    broadcast(JUMP_TO_FIRST_SELECTED);

  else
    LOG(DFATAL) << "Unknown button " << button;
}

void TransportController::setTransportState(rec::audio::transport::State state) {
  startStopButton_.setToggleState(state == rec::audio::transport::RUNNING, false);
  startStopButton_.repaint();
}

void TransportController::onDataChange(const rec::audio::Gain& gain) {
  thread::callAsync(this, &TransportController::setGain, gain);
}

void TransportController::setGain(rec::audio::Gain gain) {
  level_.setEnabled(!gain.mute());
  levelMeter_(gain);
}

void TransportController::clearLevels() {
  levelMeter_(LevelVector());
}

}  // namespace rec
}  // namespace gui
}  // namespace audio

