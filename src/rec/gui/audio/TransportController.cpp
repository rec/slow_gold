#include "rec/gui/audio/TransportController.h"

#include "rec/gui/IconButton.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

// Skin

namespace {

const int ICON_SIZE = 40;
const int MUTE_BUTTON_SIZE = 45;

}  // namespace

using rec::audio::Gain;

TransportController::TransportController(TimeController* timeController)
    : Layout("TransportController", VERTICAL),
      timeController_(timeController),
      buttonsLayout_("Buttons", HORIZONTAL),
      gainLayout_("Gain", HORIZONTAL),
      startStopButton_("Start/stop", "Start/Stop Button: Toggle between pause"
                       " and play."),
      jumpToStartButton_("Jump to start", "Jump Forward Button: "
                         "Jump to the start of the next segment."),
      jumpBackButton_("Jump Back", "Jump Back Button: "
                      "Jump to the start of the next segment."),
      jumpForwardButton_("Jump Forward", "Jump To Start Button: "
                         "Jump to the start of the track."),
      levelMeter_("LevelMeter", "Level Meter: RMS intensity for left and "
                  "right tracks."),
      level_("Volume", "Volume Slider: Raise or lower the sound intensity, "
             "in dB.", getTypeName<Gain>(), data::Address("gain")),
      muteButton_("Mute", "Mute Button: Mute or unmute the sound.",
                  getTypeName<Gain>(), data::Address("mute")) {
  startStopButton_.setClickingTogglesState(true);

  SET_BUTTON_IMAGES3(&jumpToStartButton_, JumpToStartButton);
  SET_BUTTON_IMAGES3(&jumpForwardButton_, JumpForwardButton);
  SET_BUTTON_IMAGES3(&jumpBackButton_, JumpBackButton);
  SET_BUTTON_IMAGES_ALTERNATE(&startStopButton_, PlayButton, StopButton);

  jumpForwardButton_.addListener(this);
  jumpBackButton_.addListener(this);
  jumpToStartButton_.addListener(this);
  startStopButton_.addListener(this);

  buttonsLayout_.addToLayout(&startStopButton_, ICON_SIZE);
  buttonsLayout_.addToLayout(&jumpToStartButton_, ICON_SIZE);
  buttonsLayout_.addToLayout(&jumpBackButton_, ICON_SIZE);
  buttonsLayout_.addToLayout(&jumpForwardButton_, ICON_SIZE);
  buttonsLayout_.addToLayout(timeController_);

  level_.slider()->setRange(-36.0, +12.0, 0.1);
  level_.slider()->setDetent(0.0f);
  level_.slider()->setTextValueSuffix(" dB");

  gainLayout_.addToLayout(&muteButton_, MUTE_BUTTON_SIZE);
  gainLayout_.addToLayout(&level_);

  addToLayout(&buttonsLayout_, ICON_SIZE);
  addToLayout(&gainLayout_, ICON_SIZE);
  addToLayout(&levelMeter_, 20);
}

TransportController::~TransportController() {}

using rec::audio::transport::State;

void TransportController::operator()(State state) {
  thread::callAsync(this, &TransportController::setTransportState, state);
}

void TransportController::buttonClicked(juce::Button *button) {
  using namespace rec::command;

  if (button == &startStopButton_)
    broadcast(TOGGLE_START_STOP);

  else if (button == &jumpToStartButton_)
    broadcast(JUMP_TO_FIRST);

  else if (button == &jumpBackButton_)
    broadcast(JUMP_TO_PREVIOUS);

  else if (button == &jumpForwardButton_)
    broadcast(JUMP_TO_NEXT);

  else
    LOG(DFATAL) << "Unknown button " << button;
}

void TransportController::setTransportState(rec::audio::transport::State state) {
  startStopButton_.setToggleState(state == rec::audio::transport::RUNNING, false);
  startStopButton_.repaint();
}

void TransportController::operator()(const rec::audio::Gain& gain) {
  setGain(gain);
}

void TransportController::setGain(rec::audio::Gain gain) {
  level_.setEnabled(!gain.mute());
  levelMeter_(gain);
}

void TransportController::clearLevels() {
  levelMeter_(rec::audio::LevelVector());
}

}  // namespace rec
}  // namespace gui
}  // namespace audio

