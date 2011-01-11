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
      : Layout("TimeAndLength", VERTICAL),
        label_(label),
        time_(desc),
        length_(desc),
        timeScale_(1.0) {
    label_.setJustificationType(juce::Justification::centred);\
    addToLayout(&label_);
    addToLayout(&time_);
    addToLayout(&length_);
  }

  virtual void operator()(const ClockUpdate& c) {
    if (c.time_ >= 0)
    	time_.setTime(c.time_ * timeScale_);

    if (c.length_ >= 0)
      length_.setTime(c.length_ * timeScale_);
  }

  void setTimeScale(double s) {
    s = juce::jmax(s, 0.001);
    double scale = s / timeScale_;
    time_.setTime(scale * time_.getTime());
    length_.setTime(scale * length_.getTime());
    timeScale_ = s;
  }

 private:
	gui::SimpleLabel label_;
  time::TextComponent time_;
  time::TextComponent length_;
  double timeScale_;
  ClockUpdate clockUpdate_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TimeAndLength);
};

}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_STATUS_TIMEANDLENGTH__
