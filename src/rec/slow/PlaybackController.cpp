#include "rec/slow/PlaybackController.h"
#include "rec/data/persist/Persist.h"
#include "rec/slow/Components.h"
#include "rec/slow/Slow.h"

namespace rec {
namespace slow {

using data::Address;

PlaybackController::PlaybackController(Components* comp)
    : Layout("Main controls"),
      panel_("Main panel", VERTICAL),
      timeControllerResizer_(Address("clock_x"), this, 1),
      songDataResizer_(Address("songdata_x"), this, 3),
      stretchyResizer_(Address("stretchy_y"), &panel_, 1) {
  addToLayout(&comp->timeController_);
  timeControllerResizer_.add(5);

  addToLayout(&comp->songData_);
  songDataResizer_.add(5);

  addToLayout(&panel_);
  panel_.addToLayout(&comp->playerController_, 20, -1.0, 225);
  stretchyResizer_.add(5);

  panel_.addToLayout(&comp->transportController_, 24);
}

void PlaybackController::setSetter(data::Editable* setter) {
  timeControllerResizer_.setSetter(setter);
  songDataResizer_.setSetter(setter);
  stretchyResizer_.setSetter(setter);
}

}  // namespace slow
}  // namespace rec

