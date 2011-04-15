#ifndef __REC_GUI_TRANSPORTCONTROLLER__
#define __REC_GUI_TRANSPORTCONTROLLER__

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/gui/Layout.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {

// A GUI component with three drawable buttons that broadcasts commands from
// those buttons.
class TransportController : public Layout,
                            public juce::ButtonListener,
                            public Listener<transport::State>,
                            public Broadcaster<audio::transport::Commands> {
 public:
  TransportController();
  virtual void buttonClicked(juce::Button *button);
  void setButtonState(audio::transport::Command command);
  void operator()(transport::State state);

  virtual void layout() { Layout::layout(); }

  bool getLoopPointButtonEnabled() const { return addLoopPointButton_.isEnabled(); }
  void enableLoopPointButton(bool e) { addLoopPointButton_.setEnabled(e); }

 private:
  audio::source::Player* player_;
  slow::MainPage* mainPage_;
  DrawableButton startStopButton_;
  DrawableButton addLoopPointButton_;
  DrawableButton zoomOutButton_;
  juce::Label filler_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TransportController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TRANSPORTCONTROLLER__
