#ifndef __REC_WIDGET_STATUS_DIALCOMPONENT__
#define __REC_WIDGET_STATUS_DIALCOMPONENT__

#include "rec/base/RealTime.h"
#include "rec/util/DataListener.h"
#include "rec/util/Listener.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Range.h"
#include "rec/widget/status/Time.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

class DialComponent : public Component,
                      public Listener<RealTime>,
                      public DataListener<LoopPointList> {
 public:
  explicit DialComponent(const Dial& desc);

  virtual void operator()(RealTime);

  virtual void paint(juce::Graphics& g);
  virtual void repaint() { Component::repaint(); }

  static const double PI;
  static const double REDRAW_ANGLE;

 protected:
  void onDataChange(const LoopPointList&);

 private:
  void recomputeAngle();

  CriticalSection lock_;
  Dial description_;

  RealTime time_;
  RealTime length_;
  double zeroAngle_;
  double timeAngle_;
  double timeRatio_;

  LoopPointList loops_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(DialComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_STATUS_DIALCOMPONENT__
