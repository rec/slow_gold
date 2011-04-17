#include "rec/slow/PlaybackController.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/StretchyController.h"
#include "rec/gui/Color.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/cd/Album.h"

using namespace rec::proto::arg;

using juce::Colours;
using rec::gui::Colors;
using rec::widget::status::time::Dial;
using rec::widget::status::time::DialComponent;
using rec::widget::status::time::Text;
using rec::widget::status::time::TextComponent;

namespace rec {
namespace slow {

PlaybackController::PlaybackController(Instance* instance)
    : Layout("Main controls"),
      instance_(instance),
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

  setLayoutData();
}

void PlaybackController::setLayoutData() {
  persist::Data<AppLayout>* data = persist::data<AppLayout>();

  timeControllerResizer_.setSetter(data);
  songDataResizer_.setSetter(data);
  stretchyResizer_.setSetter(data);
}

}  // namespace slow
}  // namespace rec
