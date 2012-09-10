#ifndef __REC_GUI_APP_TIMECONTROLLER__
#define __REC_GUI_APP_TIMECONTROLLER__

#include "rec/base/SampleTime.h"
#include "rec/gui/layout/Layout.h"
#include "rec/util/HasThread.h"
#include "rec/widget/status/DialComponent.h"
#include "rec/widget/status/TextComponent.h"

namespace rec {
namespace gui {
namespace audio {

class TimeController : public Layout,
                       public Listener<SampleTime>,
                       public HasThread {
 public:
  TimeController();
  virtual ~TimeController() {}

  void setTimeScale(double);

  virtual void operator()(SampleTime);
  void setLength(SampleTime);

 private:
  CriticalSection lock_;
  widget::status::time::DialComponent songDial_;
  widget::status::time::TextComponent songTime_;

  static const bool DISPLAY_SCALED_TIME = false;

  double timeScale_;
  gui::Layout filler_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TimeController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_APP_TIMECONTROLLER__
