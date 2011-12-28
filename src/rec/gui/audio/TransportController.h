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

class TimeController;

// A GUI component with three drawable buttons that broadcasts commands from
// those buttons.
class TransportController : public Layout,
                            public juce::ButtonListener,
                            public DataListener<rec::audio::Gain>,
                            public Listener<rec::audio::transport::State>,
                            public Broadcaster<CommandID> {
 public:
  TransportController(TimeController*);
  virtual ~TransportController();

  virtual void startListening();

  virtual void buttonClicked(juce::Button *button);
  virtual void operator()(rec::audio::transport::State);
  virtual void operator()(const rec::audio::Gain&);

  void setTransportState(rec::audio::transport::State state);
  void setTime(Samples<44100> time) { time_ = time; }

  util::Listener<const rec::audio::LevelVector&>* levelListener() { return &levelMeter_; }
  void clearLevels();
  LevelMeter* levelMeter() { return &levelMeter_; }

 private:
  void setGain(rec::audio::Gain);

  TimeController* timeController_;

  Layout buttonsLayout_;
  Layout gainLayout_;

  DrawableButton startStopButton_;
  DrawableButton jumpToStartButton_;
  LevelMeter levelMeter_;
  DataSlider level_;
  gui::SetterToggle muteButton_;

  juce::Label filler_;
  Samples<44100> time_;
  LoopPointList loopPointList_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TransportController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
