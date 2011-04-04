#ifndef __REC_WIDGET_STATUS_DIALCOMPONENT__
#define __REC_WIDGET_STATUS_DIALCOMPONENT__

#include "rec/util/listener/Listener.h"
#include "rec/util/ClockUpdate.h"
#include "rec/util/Range.h"
#include "rec/widget/status/Time.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

class DialComponent : public Component,
                      public Listener<const ClockUpdate&>,
                      public Listener<const SelectionRange&> {
 public:
  explicit DialComponent(const Dial& desc, double length = 0.0f, double time = 0.0f);

  void setLength(double length);
  void setTime(double time);

  virtual void operator()(const ClockUpdate& c) { c.update(this); }
  virtual void operator()(const SelectionRange& c);
  virtual void paint(juce::Graphics& g);
  virtual void repaint() { Component::repaint(); }

  static const double PI;
  static const double REDRAW_ANGLE;

 private:
  void recomputeAngle();

  CriticalSection lock_;
  Dial description_;
  double length_;
  double time_;
  TimeRange range_;
  double zeroAngle_;
  double timeAngle_;
  double timeRatio_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(DialComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_STATUS_DIALCOMPONENT__
