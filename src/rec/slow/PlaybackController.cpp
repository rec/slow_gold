#include "rec/slow/PlaybackController.h"
#include "rec/slow/Instance.h"
#include "rec/data/persist/Persist.h"

using namespace rec::proto::arg;

namespace rec {
namespace slow {

PlaybackController::PlaybackController(Instance* i, const Address& address)
    : Layout("Main controls"),
      panel_("Main panel", VERTICAL),
      timeControllerResizer_(address + "clock_x", this, 1),
      songDataResizer_(address + "songdata_x", this, 3),
      stretchyResizer_(address + "stretchy_y", &panel_, 1) {
  addToLayout(&i->components_.timeController_);
  timeControllerResizer_.add(5);
  addToLayout(&i->components_.songData_);
  songDataResizer_.add(5);
  addToLayout(&panel_);

  panel_.addToLayout(&i->components_.stretchyController_);
  stretchyResizer_.add(5);
  panel_.addToLayout(&i->components_.transportController_);
}

void PlaybackController::setSetter(persist::Setter* setter) {
  timeControllerResizer_.setSetter(setter);
  songDataResizer_.setSetter(setter);
  stretchyResizer_.setSetter(setter);
}

}  // namespace slow
}  // namespace rec

