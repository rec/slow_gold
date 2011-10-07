#ifndef __REC_GUI_APP_TIMECONTROLLER__
#define __REC_GUI_APP_TIMECONTROLLER__

#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/base/Samples.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/layout/Layout.h"
#include "rec/widget/status/DialComponent.h"
#include "rec/widget/status/TextComponent.h"

namespace rec {
namespace gui {
namespace audio {

class TimeController : public Layout, public Listener< Samples<44100> > {
 public:
  TimeController();
  virtual ~TimeController() {}

  virtual void operator()(const rec::audio::stretch::Stretch&);
  virtual void operator()(const Range<RealTime>&);
  virtual void operator()(Samples<44100>);

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
