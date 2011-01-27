#include "rec/widget/status/TimeAndLength.h"

namespace rec {
namespace widget {
namespace status {

TimeAndLength::TimeAndLength(const String& label, const time::Text& desc)
    : Layout("TimeAndLength", VERTICAL),
      label_(label),
      length_(desc),
      time_(desc),
      timeScale_(1.0) {
  label_.setJustificationType(juce::Justification::centred);
  addToLayout(&label_);
  addToLayout(&length_);
  addToLayout(&begin_);
  addToLayout(&end_);
  addToLayout(&time_);
}

void TimeAndLength::operator()(const ClockUpdate& c) {
  if (c.time_ >= 0)
    time_.setTime(c.time_ * timeScale_);

  if (c.length_ >= 0)
    length_.setTime(c.length_ * timeScale_);
}

void TimeAndLength::setTimeScale(double s) {
  s = juce::jmax(s, 0.001);
  double scale = s / timeScale_;
  time_.setTime(scale * time_.getTime());
  length_.setTime(scale * length_.getTime());
  begin_.setTime(scale * begin_.getTime());
  end_.setTime(scale * end_.getTime());

  timeScale_ = s;
}

void TimeAndLength::operator()(const SelectionRange& s) {
  TimeRange range(s);
  begin_.setTime(range.begin_);
  end_.setTime(range.end_);
}

}  // namespace status
}  // namespace widget
}  // namespace rec
