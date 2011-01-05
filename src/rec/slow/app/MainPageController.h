#ifndef __REC_SLOW_APP_MAINPAGECONTROLLER__
#define __REC_SLOW_APP_MAINPAGECONTROLLER__

#include "rec/gui/Layout.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/StretchyController.h"
#include "rec/util/listener/DataListener.h"
#include "rec/widget/status/Time.h"

namespace rec {
namespace slow {

typedef audio::source::StretchyProto StretchyProto;
typedef widget::status::time::TextComponent TextComponent;
typedef widget::status::time::DialComponent DialComponent;

class AudioTransportSourcePlayer;

class MainPageController : public gui::Layout,
                           public Listener<const AudioTransportSourcePlayer&>,
                           public juce::ButtonListener,
                           public Listener<float>,
                           public Broadcaster<float>,
                           public DataListener<StretchyProto> {
 public:
  typedef persist::Data<StretchyProto> Data;

  MainPageController(AudioTransportSourcePlayer* transportSource);

  void buttonClicked(juce::Button *button);
  void setLength(int length);

  virtual void operator()(const AudioTransportSourcePlayer& player);
  virtual void operator()(float time);
  virtual void operator()(const StretchyProto&);

  void setButtonState();
   virtual void setData(Data* data);

  void resized();

 private:
  AudioTransportSourcePlayer* transportSource_;
  juce::DrawableButton startStopButton_;
  gui::SetterToggle<StretchyProto> disableButton_;
  gui::StretchyController stretchyController_;
  TextComponent songTime_;
  DialComponent songDial_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_MAINPAGECONTROLLER__
