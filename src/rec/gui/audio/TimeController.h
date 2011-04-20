#ifndef __REC_GUI_APP_TIMECONTROLLER__
#define __REC_GUI_APP_TIMECONTROLLER__

#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Layout.h"
#include "rec/util/ClockUpdate.h"
#include "rec/widget/status/TimeAndLength.h"
#include "rec/widget/status/DialComponent.h"

namespace rec {
namespace gui {
namespace audio {

class TimeController : public Layout {
 public:
  TimeController();

  virtual void operator()(const audio::stretch::StretchLoop&);
  virtual void operator()(const Range<RealTime>&);
  virtual void operator()(RealTime);

 private:
  CriticalSection lock_;
  widget::status::time::DialComponent songDial_;
  widget::status::time::TextComponent songTime_;

  double timeScale_;

  DISALLOW_COPY_AND_ASSIGN(TimeController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_APP_TIMECONTROLLER__
