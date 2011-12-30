#include "rec/gui/audio/TransportController.h"

#include "rec/command/Command.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/gui/IconButton.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/icon/JumpBackButton.svg.h"
#include "rec/gui/icon/JumpBackButtonDisabled.svg.h"
#include "rec/gui/icon/JumpBackButtonPressed.svg.h"
#include "rec/gui/icon/JumpForwardButton.svg.h"
#include "rec/gui/icon/JumpForwardButtonDisabled.svg.h"
#include "rec/gui/icon/JumpForwardButtonPressed.svg.h"
#include "rec/gui/icon/JumpToStartButton.svg.h"
#include "rec/gui/icon/JumpToStartButtonDisabled.svg.h"
#include "rec/gui/icon/JumpToStartButtonPressed.svg.h"
#include "rec/gui/icon/PlayButton.svg.h"
#include "rec/gui/icon/PlayButtonDisabled.svg.h"
#include "rec/gui/icon/StopButton.svg.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

// TODO: i18n

namespace {

const int ICON_SIZE = 40;
const int SLIDER_HEIGHT = 18;
const int MUTE_BUTTON_SIZE = 45;

const char* const MUTE_BUTTON_TEXT = "Mute";

}  // namespace

using rec::audio::Gain;

TransportController::TransportController(TimeController* timeController)
    : Layout("TransportController", VERTICAL),
      timeController_(timeController),
      buttonsLayout_("Buttons", HORIZONTAL),
      gainLayout_("Gain", HORIZONTAL),
      startStopButton_("Start/stop", juce::DrawableButton::ImageFitted),
      jumpToStartButton_("Jump to start", juce::DrawableButton::ImageFitted),
      jumpBackButton_("Jump Back", juce::DrawableButton::ImageFitted),
      jumpForwardButton_("Jump Formward", juce::DrawableButton::ImageFitted),
      level_("Gain", getTypeName<Gain>(), data::Address("gain")),
      muteButton_(MUTE_BUTTON_TEXT, getTypeName<Gain>(), data::Address("mute")) {
  startStopButton_.setClickingTogglesState(true);

  using namespace rec::gui::icon;
  SET_BUTTON_IMAGES2(&jumpToStartButton_, JumpToStartButton);
  SET_BUTTON_IMAGES2(&jumpForwardButton_, JumpForwardButton);
  SET_BUTTON_IMAGES2(&jumpBackButton_, JumpBackButton);

  startStopButton_.setImages(ptr<Drawable>(PlayButton::create()).get(),
                             NULL, NULL,
                             ptr<Drawable>(PlayButtonDisabled::create()).get(),
                             ptr<Drawable>(StopButton::create()).get());

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

  startStopButton_.setTooltip("Toggle between pause and play.");
  jumpForwardButton_.setTooltip("Jump to the start of the next segment in the selection.");
  jumpBackButton_.setTooltip("Jump to the start of the next segment in the selection.");
  jumpToStartButton_.setTooltip("Jump to the start of the selection.");
  levelMeter_.setTooltip("Display the sound intensity, in RMS dB.");
  level_.setTooltip("Raise or lower the sound intensity, in dB.");
  muteButton_.setTooltip("Mute or unmute the sound.");
}

void TransportController::startListening() {
  DataListener<rec::audio::Gain>::startListening();
  level_.startListening();
  muteButton_.startListening();
}

TransportController::~TransportController() {}

using rec::audio::transport::State;

void TransportController::operator()(State state) {
  thread::callAsync(this, &TransportController::setTransportState, state);
}

void TransportController::buttonClicked(juce::Button *button) {
  using namespace rec::command;

  static const CommandID JUMP_BACK =
    CommandIDEncoder::toCommandID(CommandIDEncoder::PREVIOUS,
                                  Command::JUMP_SELECTED);
  static const CommandID JUMP_FORWARD =
    CommandIDEncoder::toCommandID(CommandIDEncoder::NEXT,
                                  Command::JUMP_SELECTED);

  if (button == &startStopButton_)
    broadcast(Command::TOGGLE_START_STOP);

  else if (button == &jumpToStartButton_)
    broadcast(command::JUMP_TO_FIRST_SELECTED);

  else if (button == &jumpBackButton_)
    broadcast(JUMP_BACK);

  else if (button == &jumpForwardButton_)
    broadcast(JUMP_FORWARD);

  else
    LOG(DFATAL) << "Unknown button " << button;
}

void TransportController::setTransportState(rec::audio::transport::State state) {
  startStopButton_.setToggleState(state == rec::audio::transport::RUNNING, false);
  startStopButton_.repaint();
}

void TransportController::operator()(const rec::audio::Gain& gain) {
  thread::callAsync(this, &TransportController::setGain, gain);
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

