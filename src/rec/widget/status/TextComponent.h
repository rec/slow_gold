#ifndef __REC_GUI_TIME__
#define __REC_GUI_TIME__

#include <stdio.h>

#include "rec/base/SampleTime.h"
#include "rec/util/Listener.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/widget/status/Time.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

class TextComponent : public gui::SimpleLabel,
                      public Listener<SampleTime> {
 public:
  explicit TextComponent(const Text& desc = Text::default_instance());
  virtual void operator()(SampleTime time) { setTime(time); }

  SampleTime getTime() const;
  bool setTime(SampleTime time);
  void setLength(SampleTime len) { length_ = len; }
  void redisplay();

 private:
  Text description_;
  SampleTime time_;
  String timeDisplay_;
  SampleTime length_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TextComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_GUI_TIME__
