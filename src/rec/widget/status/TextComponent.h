#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/base/RealTime.h"
#include "rec/util/Listener.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/widget/status/Time.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

class TextComponent : public gui::SimpleLabel,
                      public Listener<RealTime> {
 public:
  explicit TextComponent(const Text& desc = Text::default_instance());
  virtual void operator()(RealTime time) { setTime(time); }

  double getTime() const;
  void setTime(RealTime time);
  void setLength(RealTime len) { length_ = len; }
  void redisplay();

 private:
  CriticalSection lock_;
  Text description_;
  RealTime time_;
  String timeDisplay_;
  RealTime length_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TextComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
