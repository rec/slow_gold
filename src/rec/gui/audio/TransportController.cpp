#include "rec/gui/audio/TransportController.h"

#include "rec/gui/icon/MPStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

static const int ICON_SIZE = 30;
static const int SLIDER_HEIGHT = 18;

TransportController::TransportController()
    : Layout("TransportController", HORIZONTAL),
      startStopButton_("Start/stop", juce::DrawableButton::ImageFitted),
      level_("Gain", data::Address("gain")),
      muteButton_("Mute", data::Address("mute")) {
  level_.slider()->setRange(-36.0, +12.0, 0.1);
  level_.slider()->setDetent(0.0f);
  level_.slider()->setTextValueSuffix(" dB");
  addToLayout(&muteButton_, 14);

  addToLayout(&level_, SLIDER_HEIGHT);
  addToLayout(&levelMeter_);

  startStopButton_.setClickingTogglesState(true);
  startStopButton_.addListener(this);

  startStopButton_.setImages(
      ptr<Drawable>(icon::MediaPlaybackStart::create()).get(),
      NULL, NULL, NULL,
      ptr<Drawable>(icon::MediaPlaybackStop::create()).get());

  addToLayout(&startStopButton_, ICON_SIZE);
}

using rec::audio::transport::State;

void TransportController::operator()(State state) {
  thread::callAsync(this, &TransportController::setTransportState, state);
}

void TransportController::recalc() {
  // TODO
  // addLoopPointButton_.setEnabled(isNewLoopPointTime(loopPointList_, time_));
}

void TransportController::buttonClicked(juce::Button *button) {
  if (button == &startStopButton_)
    broadcast(command::Command::TOGGLE_START_STOP);

  else
    LOG(DFATAL) << "Unknown button " << button;
}

void TransportController::setTransportState(rec::audio::transport::State state) {
  startStopButton_.setToggleState(state == rec::audio::transport::RUNNING, false);
  startStopButton_.repaint();
}

void TransportController::onDataChange(const rec::audio::Gain& gain) {
  MessageManagerLock mml;
  level_.slider()->setEnabled(!gain.mute());
  levelMeter_(gain);
}

void TransportController::clearLevels() {
  levelMeter_(LevelVector());
}

}  // namespace rec
}  // namespace gui
}  // namespace audio

