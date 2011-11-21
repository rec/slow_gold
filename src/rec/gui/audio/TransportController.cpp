#include "rec/gui/audio/TransportController.h"

#include "rec/gui/icon/MPStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/icon/MediaPlay.svg.h"
#include "rec/gui/icon/MediaRecord.svg.h"
#include "rec/gui/icon/FullScreen.svg.h"
#include "rec/gui/icon/FullScreenRev.svg.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

TransportController::TransportController()
    : Layout("TransportController", HORIZONTAL),
      startStopButton_("Start/stop", juce::DrawableButton::ImageFitted),
      addLoopPointButton_("Add loop point", juce::DrawableButton::ImageFitted),
      zoomOutButton_("Zoom Out", juce::DrawableButton::ImageFitted) {
  startStopButton_.setClickingTogglesState(true);
  startStopButton_.addListener(this);

  startStopButton_.setImages(
      ptr<Drawable>(icon::MediaPlaybackStart::create()).get(),
      NULL, NULL, NULL,
      ptr<Drawable>(icon::MediaPlaybackStop::create()).get());

  addLoopPointButton_.addListener(this);
  addLoopPointButton_.setImages(
      ptr<Drawable>(icon::MediaPlay::create()).get(), NULL,
      ptr<Drawable>(icon::MediaRecord::create()).get());

  zoomOutButton_.addListener(this);
  zoomOutButton_.setImages(ptr<Drawable>(icon::FullScreen::create()).get(),
                           NULL,
                           ptr<Drawable>(icon::FullScreenRev::create()).get());

  addToLayout(&startStopButton_, 30, 30, 30);
  addToLayout(&addLoopPointButton_, 30, 30, 30);
  addToLayout(&zoomOutButton_, 30, 30, 30);
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

  else if (button == &addLoopPointButton_)
    broadcast(command::Command::ADD_LOOP_POINT);

  else if (button == &zoomOutButton_)
    broadcast(command::Command::ZOOM_OUT);

  else
    LOG(ERROR) << "Unknown button " << button;
}

void TransportController::setTransportState(rec::audio::transport::State state) {
  startStopButton_.setToggleState(state == rec::audio::transport::RUNNING, false);
  startStopButton_.repaint();
}

}  // namespace rec
}  // namespace gui
}  // namespace audio

