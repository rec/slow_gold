#ifndef __REC_GUI_APP_TIMECONTROLLER__
#define __REC_GUI_APP_TIMECONTROLLER__

#include "rec/base/SampleTime.h"
#include "rec/gui/proto/Panel.h"
#include "rec/util/HasThread.h"
#include "rec/widget/status/DialComponent.h"
#include "rec/widget/status/TextComponent.h"

namespace rec {
namespace gui {
namespace audio {

class TimeController : public Panel {
 public:
  TimeController();

 private:
  CriticalSection lock_;
  widget::status::time::DialComponent songDial_;
  widget::status::time::TextComponent songTime_;

  gui::Panel filler_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TimeController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_APP_TIMECONTROLLER__
