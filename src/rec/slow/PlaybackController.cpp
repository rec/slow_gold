#include "rec/slow/PlaybackController.h"
#include "rec/data/Data.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/PlayerController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/Components.h"

namespace rec {
namespace slow {

using data::Address;

PlaybackController::PlaybackController(Components* comp, data::Editable* e)
    : Layout("Main controls"),
      controllerPanel_("Main panel", VERTICAL),
      timeControllerResizer_(Address("clock_x"), this, 1, e),
      songDataResizer_(Address("songdata_x"), this, 3, e),
      stretchyResizer_(Address("stretchy_y"), &controllerPanel_, 1, e) {
  addToLayout(comp->timeController_.get(), 75, -1.0, -0.20);
  timeControllerResizer_.add(5);

  addToLayout(comp->songData_.get(), 200, -1.0, -0.40);
  songDataResizer_.add(5);

  addToLayout(&controllerPanel_);

  controllerPanel_.addToLayout(comp->playerController_.get(), 250, -1.0, -0.75);
  stretchyResizer_.add(5);
  controllerPanel_ .addToLayout(comp->transportController_.get(), 24);
}

void PlaybackController::setActive(bool a) {
  timeControllerResizer_.setActive(a);
  songDataResizer_.setActive(a);
  stretchyResizer_.setActive(a);
}

}  // namespace slow
}  // namespace rec

