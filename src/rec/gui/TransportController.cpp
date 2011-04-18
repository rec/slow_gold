#include "rec/gui/TransportController.h"

#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/icon/MediaPlay.svg.h"
#include "rec/gui/icon/MediaRecord.svg.h"
#include "rec/gui/icon/FullScreen.svg.h"
#include "rec/gui/icon/FullScreenRev.svg.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/gui/Loops.h"

using namespace rec::audio::transport;
namespace rec {
namespace gui {

TransportController::TransportController()
    : Layout("TransportController", HORIZONTAL),
      startStopButton_("Start/stop", juce::DrawableButton::ImageFitted),
      addLoopPointButton_("Add loop point", juce::DrawableButton::ImageFitted),
      zoomOutButton_("Zoom Out", juce::DrawableButton::ImageFitted) {
  startStopButton_.setClickingTogglesState(true);
  startStopButton_.addListener(this);

  startStopButton_.setImages(icon::MediaPlaybackStart::get(),
                             NULL, NULL, NULL,
                             icon::MediaPlaybackStop::get());

  addLoopPointButton_.addListener(this);
  addLoopPointButton_.setImages(icon::MediaPlay::get(), NULL,
                                icon::MediaRecord::get());

  zoomOutButton_.addListener(this);
  zoomOutButton_.setImages(icon::FullScreen::get(), NULL,
                           icon::FullScreenRev::get());

  addToLayout(&startStopButton_, 30, 30, 30);
  addToLayout(&addLoopPointButton_, 30, 30, 30);
  addToLayout(&zoomOutButton_, 30, 30, 30);
  addToLayout(&filler_);
  transport->changeBroadcaster()->addListener(this);
}

void TransportController::buttonClicked(juce::Button *button) {
  if (button == &startStopButton_)
    broadcast(TOGGLE_COMMAND);

  else if (button == &addLoopPointButton_)
    broadcast(ADD_LOOP_POINT_COMMAND);

  else if (button == &zoomOutButton_)
    broadcast(ZOOM_OUT_COMMAND);

  else
    LOG(ERROR) << "Unknown button " << button;
}

void TransportController::setButtonState(audio::transport::State state) {
  startStopButton_.setToggleState(state == audio::RUNNING, false);
  startStopButton_.repaint();
}

void TransportController::recalc() {
  addLoopPointButton_.setEnabled(isNewLoopPoint(loopPointList_, time_));
}

}  // namespace gui
}  // namespace rec

