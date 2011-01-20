#ifndef __REC_GUI_TRANSPORTCONTROLLER__
#define __REC_GUI_TRANSPORTCONTROLLER__

#include "rec/gui/Layout.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer;
class MainPage;

}  // namespace slow

namespace gui {

class TransportController : public Layout,
                            public juce::ButtonListener,
                            public Listener<const slow::AudioTransportSourcePlayer&> {
 public:
  TransportController(slow::AudioTransportSourcePlayer* transport,
                      slow::MainPage* mp);
  virtual void buttonClicked(juce::Button *button);
  void setButtonState();
  void operator()(const slow::AudioTransportSourcePlayer& player);

  virtual void layout() { Layout::layout(); }

  bool getLoopPointButtonEnabled() const { return addLoopPointButton_.isEnabled(); }
  void enableLoopPointButton(bool e) { addLoopPointButton_.setEnabled(e); }

 private:
  slow::AudioTransportSourcePlayer* transport_;
  slow::MainPage* mainPage_;
  juce::DrawableButton startStopButton_;
  juce::DrawableButton addLoopPointButton_;
  juce::Label filler_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TransportController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TRANSPORTCONTROLLER__
