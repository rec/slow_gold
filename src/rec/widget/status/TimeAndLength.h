#ifndef __REC_WIDGET_STATUS_TIMEANDLENGTH__
#define __REC_WIDGET_STATUS_TIMEANDLENGTH__

#include "rec/widget/status/Time.h"
#include "rec/gui/Layout.h"
#include "rec/gui/SimpleLabel.h"

namespace rec {
namespace widget {
namespace status {

class TimeAndLength : public gui::Layout, public Listener<const ClockUpdate&> {
 public:
  TimeAndLength(const String& label,
                const time::Text& desc = time::Text::default_instance())
      : Layout("TimeAndLength", VERTICAL), label_(label), time_(desc), length_(desc) {
    addToLayout(&label_);
    addToLayout(&time_);
    addToLayout(&length_);
  }

  virtual void operator()(const ClockUpdate& c) {
    time_.setTime(c.time_);
    length_.setTime(c.length_);
  }

 private:
	gui::SimpleLabel label_;
  time::TextComponent time_;
  time::TextComponent length_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TimeAndLength);
};

}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_STATUS_TIMEANDLENGTH__
