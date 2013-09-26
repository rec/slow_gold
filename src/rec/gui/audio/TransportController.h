#ifndef __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
#define __REC_GUI_AUDIO_TRANSPORTCONTROLLER__

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/command/Command.pb.h"
#include "rec/gui/LanguageButton.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/audio/LevelMeter.h"
#include "rec/gui/proto/Panel.h"
#include "rec/util/Listener.h"

namespace rec {
namespace gui {
namespace audio {

class TimeController;

enum TransportCommand {
  TOGGLE_START_STOP,
  JUMP_TO_FIRST,
  JUMP_TO_PREVIOUS,
  JUMP_TO_NEXT,
};

// A GUI component with three drawable buttons that broadcasts commands from
// those buttons.
class TransportController : public Panel,
                            public juce::ButtonListener,
                            public DataListener<rec::audio::Gain>,
                            public Listener<rec::audio::transport::State>,
                            public Broadcaster<TransportCommand> {
 public:
  TransportController();
  virtual ~TransportController();

  void addTimeController(Component*);
  virtual void buttonClicked(juce::Button *button);
  virtual void operator()(rec::audio::transport::State);
  virtual void operator()(const rec::audio::Gain&);

  void setTransportState(rec::audio::transport::State state);

  util::Listener<const rec::audio::LevelVector&>* levelListener() { return &levelMeter_; }
  void clearLevels();
  LevelMeter* levelMeter() { return &levelMeter_; }

 private:
  void setGain(rec::audio::Gain);

  Panel buttonsPanel_;
  Panel gainPanel_;

  LanguageButton startStopButton_;
  LanguageButton jumpToStartButton_;
  LanguageButton jumpBackButton_;
  LanguageButton jumpForwardButton_;
  LevelMeter levelMeter_;
  DataSlider level_;
  gui::SetterToggle muteButton_;

  juce::Label filler_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TransportController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
