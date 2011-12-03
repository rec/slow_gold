#ifndef __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
#define __REC_GUI_AUDIO_TRANSPORTCONTROLLER__

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/command/Command.pb.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/audio/LevelMeter.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/Listener.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace gui {
namespace audio {

// A GUI component with three drawable buttons that broadcasts commands from
// those buttons.
class TransportController : public Layout,
                            public juce::ButtonListener,
                            public DataListener<rec::audio::Gain>,
                            public Listener<rec::audio::transport::State>,
                            public Broadcaster<command::Command::Type> {
 public:
  TransportController();

  virtual void buttonClicked(juce::Button *button);
  virtual void operator()(rec::audio::transport::State);
  virtual void onDataChange(const rec::audio::Gain&);

  void setTransportState(rec::audio::transport::State state);
  void setTime(Samples<44100> time) { time_ = time; recalc(); }

  listener::Listener<const LevelVector&>* levelListener() { return &levelMeter_; }
  void clearLevels();
  LevelMeter* levelMeter() { return &levelMeter_; }

 private:
  void recalc();

  DrawableButton startStopButton_;
  LevelMeter levelMeter_;
  DataSlider<rec::audio::Gain, double> level_;
  gui::SetterToggle<rec::audio::Gain> muteButton_;

  juce::Label filler_;
  Samples<44100> time_;
  LoopPointList loopPointList_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TransportController);
};



}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
