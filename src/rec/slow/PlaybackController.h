#ifndef __REC_SLOW_APP_PLAYBACKCONTROLLER__
#define __REC_SLOW_APP_PLAYBACKCONTROLLER__

#include "rec/gui/Layout.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/gui/SetterTextArea.h"
#include "rec/gui/SetterResizer.h"
#include "rec/gui/SongData.h"
#include "rec/gui/StretchyController.h"
#include "rec/gui/TransportController.h"
#include "rec/util/listener/DataListener.h"
#include "rec/slow/TimeController.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/AudioTransportSourcePlayer.h"

namespace rec {
namespace slow {

class MainPage;
using namespace widget::status::time;

typedef audio::stretch::StretchLoop StretchLoop;

class PlaybackController : public gui::Layout,
                           public Listener<const VirtualFile&>,
                           public DataListener<StretchLoop> {
 public:
  typedef persist::Data<StretchLoop> Data;
  typedef gui::SetterResizer SetterResizer;

  PlaybackController(AudioTransportSourcePlayer* transport, MainPage* mainPage);

  void setLayoutData();

  virtual void operator()(const VirtualFile&);
  virtual void operator()(const StretchLoop&);

  virtual void setData(Data* data);

  void enableLoopPointButton(bool e);
  TimeController* timeController() { return &timeController_; }
  gui::StretchyController* stretchyController() { return &stretchyController_; }

 private:
  TimeController timeController_;
  SetterResizer timeControllerResizer_;

  gui::SongData songData_;
  SetterResizer songDataResizer_;

  Layout panel_;
  gui::StretchyController stretchyController_;
  SetterResizer stretchyResizer_;
  gui::TransportController transportController_;

  DISALLOW_COPY_AND_ASSIGN(PlaybackController);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_PLAYBACKCONTROLLER__
