#ifndef __REC_SLOW_APP_PLAYBACKCONTROLLER__
#define __REC_SLOW_APP_PLAYBACKCONTROLLER__

#include "rec/gui/Layout.h"
#include "rec/gui/SetterTextArea.h"
#include "rec/gui/StretchyController.h"
#include "rec/util/listener/DataListener.h"
#include "rec/widget/status/Time.h"
#include "rec/util/cd/Album.pb.h"

namespace rec {
namespace slow {

typedef audio::source::StretchyProto StretchyProto;
typedef widget::status::time::TextComponent TextComponent;
typedef widget::status::time::DialComponent DialComponent;

class AudioTransportSourcePlayer;

class PlaybackController : public gui::Layout,
                           public Listener<const AudioTransportSourcePlayer&>,
                           public Listener<const VolumeFile&>,
                           public juce::ButtonListener,
                           public Listener<float>,
                           public Broadcaster<float>,
                           public DataListener<StretchyProto> {
 public:
  typedef persist::Data<StretchyProto> Data;

  PlaybackController();
  void setTransport(AudioTransportSourcePlayer* transportSource);

  void buttonClicked(juce::Button *button);
  void setLength(int length);

  virtual void operator()(const AudioTransportSourcePlayer& player);
  virtual void operator()(float time);
  virtual void operator()(const StretchyProto&);
  virtual void operator()(const VolumeFile&);

  void setButtonState();
  virtual void setData(Data* data);

  void resized();

 private:
  AudioTransportSourcePlayer* transportSource_;
  juce::DrawableButton startStopButton_;
  gui::StretchyController stretchyController_;
  TextComponent songTime_;
  DialComponent songDial_;
  gui::SetterTextArea<cd::Metadata> songData_;

  DISALLOW_COPY_AND_ASSIGN(PlaybackController);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_PLAYBACKCONTROLLER__
