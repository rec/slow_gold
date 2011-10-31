#ifndef __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
#define __REC_GUI_AUDIO_TRANSPORTCONTROLLER__

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/command/Command.pb.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace gui {
namespace audio {

// A GUI component with three drawable buttons that broadcasts commands from
// those buttons.
class TransportController : public Layout,
                            public juce::ButtonListener,
                            public Listener<rec::audio::transport::State>,
                            public Broadcaster<command::Command::Type> {
 public:
  TransportController();

  virtual void buttonClicked(juce::Button *button);
  virtual void operator()(rec::audio::transport::State);

  void setTransportState(rec::audio::transport::State state);
  void setTime(Samples<44100> time) { time_ = time; recalc(); }

 private:
  void recalc();

  DrawableButton startStopButton_;
  DrawableButton addLoopPointButton_;
  DrawableButton zoomOutButton_;

  juce::Label filler_;
  Samples<44100> time_;
  LoopPointList loopPointList_;

  DISALLOW_COPY_AND_ASSIGN(TransportController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
