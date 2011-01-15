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
#include "rec/slow/app/TimeController.h"
#include "rec/slow/app/AppLayout.pb.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"

namespace rec {
namespace slow {

typedef audio::source::StretchyProto StretchyProto;
typedef widget::status::time::TextComponent TextComponent;
typedef widget::status::time::DialComponent DialComponent;


class PlaybackController : public gui::Layout,
                           public Listener<const VirtualFile&>,
                           public DataListener<StretchyProto> {
 public:
  typedef persist::Data<StretchyProto> Data;
  typedef gui::SetterResizer SetterResizer;

  PlaybackController(AudioTransportSourcePlayer* transport);

  void setLayoutData();

  virtual void operator()(const VirtualFile&);
  virtual void operator()(const StretchyProto&);

  virtual void setData(Data* data);

  TimeController* timeController() { return &timeController_; }

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
