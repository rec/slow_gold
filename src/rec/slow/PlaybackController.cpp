#include "rec/slow/PlaybackController.h"
#include "rec/data/Data.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/PlayerController.h"
#include "rec/slow/Components.h"
#include "rec/slow/Slow.h"

namespace rec {
namespace slow {

using data::Address;

PlaybackController::PlaybackController(Components* comp, data::Editable* e)
    : Layout("Main controls"),
      panel_("Main panel", VERTICAL),
      timeControllerResizer_(Address("clock_x"), this, 1, e),
      songDataResizer_(Address("songdata_x"), this, 3, e),
      stretchyResizer_(Address("stretchy_y"), &panel_, 1, e) {
  addToLayout(comp->timeController_.get());
  timeControllerResizer_.add(5);

  addToLayout(comp->songData_.get());
  songDataResizer_.add(5);

  addToLayout(&panel_);
  panel_.addToLayout(comp->playerController_.get(), 20, -1.0, 225);
  stretchyResizer_.add(5);

  panel_.addToLayout(&comp->transportController_, 24);
}

void PlaybackController::setActive(bool a) {
  timeControllerResizer_.setActive(a);
  songDataResizer_.setActive(a);
  stretchyResizer_.setActive(a);
}

}  // namespace slow
}  // namespace rec

