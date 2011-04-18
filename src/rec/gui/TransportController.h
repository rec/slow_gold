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
                            public Broadcaster<audio::transport::Commands> {
 public:
  TransportController();
  virtual void buttonClicked(juce::Button *button);
  void setTransportState(audio::transport::State state);
  void setTime(SampleTime time) { time_ = time; recalc(); }
  void setLoopPoints(const LoopPointList& lp) { loopPointList_ = lp; recalc(); }

 private:
  void recalc();

  audio::source::Player* player_;
  slow::MainPage* mainPage_;
  DrawableButton startStopButton_;
  DrawableButton addLoopPointButton_;
  DrawableButton zoomOutButton_;
  juce::Label filler_;
  SampleTime time_;
  LoopPointList loopPointList_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TransportController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TRANSPORTCONTROLLER__
