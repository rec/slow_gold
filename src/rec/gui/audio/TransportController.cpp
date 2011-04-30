#include "rec/gui/audio/TransportController.h"

#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/icon/MediaPlay.svg.h"
#include "rec/gui/icon/MediaRecord.svg.h"
#include "rec/gui/icon/FullScreen.svg.h"
#include "rec/gui/icon/FullScreenRev.svg.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/gui/audio/Loops.h"

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
  DLOG(INFO) << "setTransportState " << state;
  startStopButton_.setToggleState(state == rec::audio::transport::RUNNING, false);
  startStopButton_.repaint();
}

void TransportController::recalc() {
  addLoopPointButton_.setEnabled(isNewLoopPointTime(loopPointList_, time_));
}

}  // namespace rec
}  // namespace gui
}  // namespace audio

