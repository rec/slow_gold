#ifndef __REC_SLOW_APP_TIMECONTROLLER__
#define __REC_SLOW_APP_TIMECONTROLLER__

#include "rec/gui/Layout.h"
#include "rec/data/persist/Persist.h"
#include "rec/widget/status/Time.h"
#include "rec/audio/source/Stretchy.pb.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer;

class TimeController : public gui::Layout,
                       public Listener<const AudioTransportSourcePlayer&>,
                       public juce::ButtonListener {
 public:
  typedef persist::Data<audio::source::StretchyProto> Data;

  TimeController();
  void setTransport(AudioTransportSourcePlayer* transportSource);

  void buttonClicked(juce::Button *button);
  void setLength(int length);

  virtual void operator()(const AudioTransportSourcePlayer& player);

  void setButtonState();

 private:
  Layout transportLayout_;
  Layout timesAndClockLayout_;
  Layout timesLayout_;

  AudioTransportSourcePlayer* transportSource_;
  juce::DrawableButton startStopButton_;

  widget::status::time::TextComponent songTime_;
  widget::status::time::DialComponent songDial_;

  DISALLOW_COPY_AND_ASSIGN(TimeController);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_TIMECONTROLLER__
