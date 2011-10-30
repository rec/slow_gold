#ifndef __REC_SLOW_APP_PLAYBACKCONTROLLER__
#define __REC_SLOW_APP_PLAYBACKCONTROLLER__

#include "rec/gui/layout/Layout.h"
#include "rec/gui/SetterResizer.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/TimeController.h"

namespace rec {
namespace slow {

class Components;

class PlaybackController {
 public:
  explicit PlaybackController(Components* i, data::Editable* setter);
  void setActive(bool a);
  gui::Layout* panel() { return &playbackPanel_; }

 private:
  gui::Layout playbackPanel_;
  gui::Layout controllerPanel_;

  gui::SetterResizer timeControllerResizer_;
  gui::SetterResizer songDataResizer_;
  gui::SetterResizer stretchyResizer_;

  DISALLOW_COPY_AND_ASSIGN(PlaybackController);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_APP_PLAYBACKCONTROLLER__
