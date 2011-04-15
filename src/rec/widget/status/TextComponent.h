#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/util/listener/Listener.h"
#include "rec/util/ClockUpdate.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/widget/status/Time.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

class TextComponent : public gui::SimpleLabel, public Listener<RealTime> {
 public:
  explicit TextComponent(const Text& desc = Text::default_instance());
  virtual void operator()(RealTime time) { setTime(time); }

  double getTime() const;
  void setTime(double time);
  void redisplay();

 private:
  CriticalSection lock_;
  Text description_;
  double time_;
  String timeDisplay_;

  DISALLOW_COPY_AND_ASSIGN(TextComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
