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

class TimeController : public Layout, public Listener<SampleTime> {
 public:
  TimeController();
  virtual ~TimeController() {}

  virtual void operator()(const rec::audio::stretch::Stretch&);
  virtual void operator()(const Range<RealTime>&);
  virtual void operator()(SampleTime);

 private:
  CriticalSection lock_;
  widget::status::time::DialComponent songDial_;
  widget::status::time::TextComponent songTime_;

  double timeScale_;
  gui::Layout timesLayout_;

  DISALLOW_COPY_AND_ASSIGN(TimeController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_APP_TIMECONTROLLER__
