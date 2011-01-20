#include "rec/gui/TransportController.h"

#include "rec/slow/AudioTransportSourcePlayer.h"
#include "rec/slow/MainPage.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"
#include "rec/gui/icon/MediaPlay.svg.h"
#include "rec/gui/icon/MediaRecord.svg.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

TransportController::TransportController(
   slow::AudioTransportSourcePlayer* transport,
   slow::MainPage* mainPage)
    : Layout("TransportController", HORIZONTAL),
      transport_(transport),
      mainPage_(mainPage),
      startStopButton_("Start/stop", juce::DrawableButton::ImageFitted),
      addLoopPointButton_("Add loop point", juce::DrawableButton::ImageFitted) {
  startStopButton_.setClickingTogglesState(true);
  startStopButton_.addListener(this);

  startStopButton_.setImages(icon::MediaPlaybackStart::get(),
                             NULL, NULL, NULL,
                             icon::MediaPlaybackStop::get());

  addLoopPointButton_.addListener(this);
  addLoopPointButton_.setImages(icon::MediaPlay::get(), NULL,
                                icon::MediaRecord::get());

  addToLayout(&startStopButton_, 30, 30, 30);
  addToLayout(&addLoopPointButton_, 30, 30, 30);
  addToLayout(&filler_);
  transport->changeBroadcaster()->addListener(this);
}

void TransportController::buttonClicked(juce::Button *button) {
  if (button == &startStopButton_)
    transport_->toggle();

  else if (button == &addLoopPointButton_)
    mainPage_->addLoopPoint();
}

void TransportController::setButtonState() {
  startStopButton_.setToggleState(transport_->isPlaying(), false);
  startStopButton_.repaint();
}

void TransportController::operator()(const slow::AudioTransportSourcePlayer& player) {
  thread::callAsync(this, &TransportController::setButtonState);
}

}  // namespace gui
}  // namespace rec

