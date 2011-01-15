#ifndef __REC_GUI_TRANSPORTCONTROLLER__
#define __REC_GUI_TRANSPORTCONTROLLER__

#include "rec/gui/Layout.h"
#include "rec/slow/AudioTransportSourcePlayer.h"
#include "rec/gui/icon/MediaPlaybackStart.svg.h"
#include "rec/gui/icon/MediaPlaybackStop.svg.h"

namespace rec {
namespace gui {

class TransportController : public Layout,
                            public juce::ButtonListener,
                            public Listener<const slow::AudioTransportSourcePlayer&> {
 public:
  TransportController(slow::AudioTransportSourcePlayer* transport)
      : Layout("TransportController", HORIZONTAL),
        transport_(transport),
        startStopButton_("Start/stop", juce::DrawableButton::ImageFitted) {
    startStopButton_.setClickingTogglesState(true);
    startStopButton_.addListener(this);

    startStopButton_.setImages(gui::icon::MediaPlaybackStart::get(),
                               NULL, NULL, NULL,
                               gui::icon::MediaPlaybackStop::get());
    addToLayout(&startStopButton_, 30, 30, 30);
    addToLayout(&filler_);
    transport->changeBroadcaster()->addListener(this);
  }

  void buttonClicked(juce::Button *button) {
    if (button == &startStopButton_)
      transport_->toggle();
  }

  void setButtonState() {
    startStopButton_.setToggleState(transport_->isPlaying(), false);
    startStopButton_.repaint();
  }

  void operator()(const slow::AudioTransportSourcePlayer& player) {
    thread::callAsync(this, &TransportController::setButtonState);
  }

  virtual void layout() {
    Layout::layout();
  }

 private:
  slow::AudioTransportSourcePlayer* transport_;
  juce::DrawableButton startStopButton_;
  juce::Label filler_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(TransportController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TRANSPORTCONTROLLER__
