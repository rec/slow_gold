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
#include "rec/slow/Player.h"

namespace rec {
namespace slow {

using namespace widget::status::time;

typedef audio::stretch::StretchLoop StretchLoop;

class PlaybackController : public gui::Layout,
                           public Listener<const VirtualFile&>,
                           public DataListener<StretchLoop>,
                           public Listener<RealTime> {
 public:
  typedef persist::Data<StretchLoop> Data;
  typedef gui::SetterResizer SetterResizer;

  PlaybackController(Player* player);

  void setLayoutData();

  virtual void operator()(const VirtualFile&);
  virtual void operator()(const StretchLoop&);
  virtual void operator()(RealTime);

  virtual void setData(Data* data);

  void enableLoopPointButton(bool e);

 private:
  Layout panel_;

  SetterResizer timeControllerResizer_;
  SetterResizer songDataResizer_;
  SetterResizer stretchyResizer_;

  DISALLOW_COPY_AND_ASSIGN(PlaybackController);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_PLAYBACKCONTROLLER__
