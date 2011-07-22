#include "rec/slow/PlaybackController.h"
#include "rec/data/persist/Persist.h"
#include "rec/slow/Components.h"
#include "rec/slow/Slow.h"

namespace rec {
namespace slow {

PlaybackController::PlaybackController(Components* comp, const Address& address)
    : Layout("Main controls"),
      panel_("Main panel", VERTICAL),
      timeControllerResizer_(address + "clock_x", this, 1),
      songDataResizer_(address + "songdata_x", this, 3),
      stretchyResizer_(address + "stretchy_y", &panel_, 1) {
  addToLayout(&comp->timeController_);
  timeControllerResizer_.add(5);

  addToLayout(&comp->songData_);
  songDataResizer_.add(5);

  addToLayout(&panel_);
  panel_.addToLayout(&comp->playerController_, 225, -1.0, 225);
  stretchyResizer_.add(5);

  panel_.addToLayout(&comp->transportController_, 24);
}

void PlaybackController::setSetter(data::Data* setter) {
  timeControllerResizer_.setSetter(setter);
  songDataResizer_.setSetter(setter);
  stretchyResizer_.setSetter(setter);
}

}  // namespace slow
}  // namespace rec

