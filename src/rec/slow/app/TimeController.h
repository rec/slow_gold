#ifndef __REC_SLOW_APP_TIMECONTROLLER__
#define __REC_SLOW_APP_TIMECONTROLLER__

#include "rec/audio/source/Stretchy.pb.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Layout.h"
#include "rec/slow/app/AudioTransportSourcePlayer.h"
#include "rec/util/ClockUpdate.h"
#include "rec/widget/status/TimeAndLength.h"
#include "rec/audio/source/Stretchy.pb.h"

namespace rec {
namespace slow {

class AudioTransportSourcePlayer;

class TimeController : public gui::Layout,
                       public Listener<float>,
                       public Listener<const audio::source::StretchyProto&>,
                       public Listener<const ClockUpdate&>,
                       public Broadcaster<const ClockUpdate&> {
 public:
  typedef persist::Data<audio::source::StretchyProto> Data;

  TimeController(AudioTransportSourcePlayer* transportSource);

  virtual void operator()(const ClockUpdate& up) { broadcast(up); }
  virtual void operator()(const audio::source::StretchyProto&);
  virtual void operator()(float time) {
    broadcast(ClockUpdate(time, -1));
  }

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
