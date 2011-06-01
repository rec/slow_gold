#ifndef __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
#define __REC_GUI_AUDIO_TRANSPORTCONTROLLER__

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/command/Command.pb.h"
#include "rec/gui/Layout.h"
#include "rec/gui/audio/GainController.h"
#include "rec/gui/audio/LevelMeter.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {
namespace audio {


// A GUI component with three drawable buttons that broadcasts commands from
// those buttons.
class TransportController : public Layout,
                            public juce::ButtonListener,
                            public Broadcaster<command::Command::Type> {
 public:
  TransportController();
  virtual void buttonClicked(juce::Button *button);
  void setTransportState(rec::audio::transport::State state);
  void setTime(SampleTime time) { time_ = time; recalc(); }
  void setLoopPoints(const LoopPointList& lp) { loopPointList_ = lp; recalc(); }
  listener::Listener<const LevelVector&>* levelListener() { return &levelMeter_; }
  LevelMeter* levelMeter() { return &levelMeter_; }
  GainController* gainController() { return &gainController_; }

 private:
  void recalc();

  DrawableButton startStopButton_;
  DrawableButton addLoopPointButton_;
  DrawableButton zoomOutButton_;
  GainController gainController_;
  LevelMeter levelMeter_;

  juce::Label filler_;
  SampleTime time_;
  LoopPointList loopPointList_;

  DISALLOW_COPY_AND_ASSIGN(TransportController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
