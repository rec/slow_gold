#pragma once

#include "rec/base/SampleTime.h"
#include "rec/data/DataListener.h"
#include "rec/util/Disableable.h"
#include "rec/util/HasThread.h"
#include "rec/util/Listener.h"
#include "rec/util/StateListener.h"
#include "rec/util/range/Range.h"
#include "rec/widget/status/Time.pb.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace widget {
namespace status {
namespace time {

class DialComponent : public Component,
                                            public Disableable,
                                            public StateListener<SampleTime>,
                                            public StateListener<Thread*>,
                                            public DataListener<waveform::Viewport>,
                                            public SettableTooltipClient,
                                            public HasThread {
  public:
    explicit DialComponent(const Dial& desc);

    virtual void operator()(SampleTime t) { setTime(t); }

    virtual void paint(juce::Graphics& g);
    void setTime(SampleTime);

    static const double PI;
    static const double REDRAW_ANGLE;

  protected:
    void operator()(Thread* t) override { setThread(t); }
    void operator()(const waveform::Viewport&) override;

  private:
    void recomputeAngle();
    bool doSetTime(SampleTime);

    CriticalSection lock_;
    Dial description_;

    SampleTime time_;
    SampleTime length_;

    double zeroAngle_;
    double timeAngle_;
    double timeRatio_;

    LoopPointList loops_;
    bool empty_;

    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(DialComponent);
};

}  // namespace time
}  // namespace status
}  // namespace widget
}  // namespace rec
