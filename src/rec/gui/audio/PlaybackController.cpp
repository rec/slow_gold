#include "rec/slow/PlaybackController.h"
#include "rec/data/persist/Persist.h"
#include "rec/slow/AppLayout.pb.h"

using namespace rec::proto::arg;

namespace rec {
namespace gui {
namespace audio {

PlaybackController::PlaybackController(Instance* instance)
    : Layout("Main controls"),
      timeController_(transport),
      timeControllerResizer_(Address("clock_x"), this, 1),
      songDataResizer_(Address("songdata_x"), this, 3),
      panel_("Main panel", VERTICAL),
      stretchyResizer_(Address("stretchy_y"), &panel_, 1),
      transportController_(transport, mainPage) {
  addToLayout(&timeController_);
  timeControllerResizer_.add(5);
  addToLayout(&songData_);
  songDataResizer_.add(5);
  addToLayout(&panel_);

  panel_.addToLayout(&stretchyController_);
  stretchyResizer_.add(5);
  panel_.addToLayout(&transportController_);

  persist::Data<AppLayout>* data = persist::data<AppLayout>();

  timeControllerResizer_.setSetter(data);
  songDataResizer_.setSetter(data);
  stretchyResizer_.setSetter(data);
}

