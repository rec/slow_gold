#ifndef __REC_WIDGET_STATUS_DIALCOMPONENT__
#define __REC_WIDGET_STATUS_DIALCOMPONENT__

#include "rec/base/SampleTime.h"
#include "rec/data/DataListener.h"
#include "rec/util/Listener.h"
#include "rec/util/Range.h"
#include "rec/widget/status/Time.pb.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

class DialComponent : public Component,
                      public Listener<SampleTime >,
                      public DataListener<waveform::Viewport>,
                      public SettableTooltipClient {
 public:
  explicit DialComponent(const Dial& desc);

  virtual void operator()(SampleTime t);

  virtual void paint(juce::Graphics& g);
  virtual void repaint() { Component::repaint(); }
  bool setTime(SampleTime);

  static const double PI;
  static const double REDRAW_ANGLE;

 protected:
  virtual void operator()(const waveform::Viewport&);

 private:
  void recomputeAngle();

  CriticalSection lock_;
  Dial description_;

  SampleTime time_;
  SampleTime length_;

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
