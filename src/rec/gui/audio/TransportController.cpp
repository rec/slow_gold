#include "rec/gui/audio/TransportController.h"

#include "rec/gui/IconButton.h"
#include "rec/gui/proto/Layout.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/slow/Instance.h"
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

TransportController::TransportController()
    : Panel("TransportController", VERTICAL),
      buttonsPanel_("Buttons", HORIZONTAL),
      timeController_(gui::makeLayout("TimeController", this)),
      startStopButton_("StartStopButton", "Start/Stop Button: Toggle between pause "
                       "and play."),
      jumpToStartButton_("Jump to start", "Jump Forward Button: "
                         "Jump to the start of the next segment."),
      jumpBackButton_("Jump Back", "Jump Back Button: "
                      "Jump to the start of the next segment."),
      jumpForwardButton_("Jump Forward", "Jump To Start Button: "
                         "Jump to the start of the track."),
      levelMeter_("LevelMeter", "Level Meter: RMS intensity for left and "
                  "right tracks.") {

  Component* buttonsPanel;
  if (slow::Instance::USE_NEW_GUI) {
    buttonsPanel2_ = gui::makeLayout("TransportButtonsPanel", this);
    buttonsPanel = buttonsPanel2_.get();
  } else {
    startStopButton_.setClickingTogglesState(true);

    SET_BUTTON_IMAGES3(&jumpToStartButton_, JumpToStartButton);
    SET_BUTTON_IMAGES3(&jumpForwardButton_, JumpForwardButton);
    SET_BUTTON_IMAGES3(&jumpBackButton_, JumpBackButton);
    SET_BUTTON_IMAGES_ALTERNATE(
        &startStopButton_, StartStopButton, StartStopButtonOn);

    jumpForwardButton_.addListener(this);
    jumpBackButton_.addListener(this);
    jumpToStartButton_.addListener(this);
    startStopButton_.addListener(this);

    buttonsPanel_.addToPanel(&startStopButton_, ICON_SIZE);
    buttonsPanel_.addToPanel(&jumpToStartButton_, ICON_SIZE);
    buttonsPanel_.addToPanel(&jumpBackButton_, ICON_SIZE);
    buttonsPanel_.addToPanel(&jumpForwardButton_, ICON_SIZE);
    buttonsPanel_.addToPanel(timeController_.get());
    buttonsPanel = &buttonsPanel_;
  }

  addToPanel(buttonsPanel, ICON_SIZE);

  gainPanel_ = gui::makeLayout("GainPanel", this);
  addToPanel(gainPanel_.get(), ICON_SIZE);
  addToPanel(&levelMeter_, 20);
}

TransportController::~TransportController() {}

using rec::audio::transport::State;

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

}  // namespace rec
}  // namespace gui
}  // namespace audio
