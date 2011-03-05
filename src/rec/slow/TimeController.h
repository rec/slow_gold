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

class AudioTransportSourcePlayer;

class TimeController : public gui::Layout,
                       public Listener<double>,
                       public Listener<const audio::stretch::StretchLoop&>,
                       public Listener<const SelectionRange&>,
                       public Listener<const ClockUpdate&>,
                       public Broadcaster<const ClockUpdate&> {
 public:
  typedef audio::stretch::StretchLoop StretchLoop;
  typedef persist::Data<StretchLoop> Data;

  TimeController(AudioTransportSourcePlayer* transportSource);

  virtual void operator()(const ClockUpdate& up) { broadcast(up); }
  virtual void operator()(const StretchLoop&);
  virtual void operator()(double t) { broadcast(ClockUpdate(t, -1)); }

  virtual void operator()(const SelectionRange&);

 private:
  AudioTransportSourcePlayer* transportSource_;

  Layout timesLayout_;

  widget::status::time::DialComponent songDial_;

  widget::status::TimeAndLength realTime_;
  widget::status::TimeAndLength songTime_;

  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(TimeController);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_TIMECONTROLLER__
