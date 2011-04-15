#ifndef __REC_SLOW_APP_TIMECONTROLLER__
#define __REC_SLOW_APP_TIMECONTROLLER__

#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Layout.h"
#include "rec/slow/AudioTransportSourcePlayer.h"
#include "rec/util/ClockUpdate.h"
#include "rec/widget/status/TimeAndLength.h"
#include "rec/widget/status/DialComponent.h"

namespace rec {
namespace slow {

class TimeController : public gui::Layout,
                       public Listener<RealTime>,
                       public Listener<const Range<RealTime>&>,
                       public Listener<const audio::stretch::StretchLoop&> {
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

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_TIMECONTROLLER__
