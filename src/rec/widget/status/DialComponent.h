#ifndef __REC_WIDGET_STATUS_DIALCOMPONENT__
#define __REC_WIDGET_STATUS_DIALCOMPONENT__

#include "rec/base/Samples.h"
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
                      public Listener<Samples<44100> >,
                      public DataListener<LoopPointList> {
 public:
  explicit DialComponent(const Dial& desc);

  virtual void operator()(Samples<44100>);

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

  Samples<44100> time_;
  Samples<44100> length_;
  double zeroAngle_;
  double timeAngle_;
  double timeRatio_;

  LoopPointList loops_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(DialComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_STATUS_DIALCOMPONENT__
