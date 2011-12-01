#include "rec/gui/audio/TransportController.h"

#include "rec/gui/icon/MPStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

static const int ICON_SIZE = 30;

TransportController::TransportController()
    : Layout("TransportController", HORIZONTAL),
      startStopButton_("Start/stop", juce::DrawableButton::ImageFitted) {
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

}  // namespace rec
}  // namespace gui
}  // namespace audio

