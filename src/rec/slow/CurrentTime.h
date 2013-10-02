#ifndef __REC_SLOW_CURRENTTIME__
#define __REC_SLOW_CURRENTTIME__

#include "rec/audio/Audio.h"
#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/util/CurrentTimeBase.h"
#include "rec/base/SampleTime.h"
#include "rec/data/DataListener.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/util/Listener.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/StateListener.h"
#include "rec/util/range/Range.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace slow {

class CurrentTime : public audio::util::CurrentTimeBase,
                    public DataListener<widget::waveform::Viewport>,
                    public DataListener<GuiSettings>,
                    public StateListener<SampleTime>,
                    public StateListener<audio::transport::State> {
 public:
  CurrentTime();
  virtual ~CurrentTime() {}

  void setTime(SampleTime);
  void setViewport(const widget::waveform::Viewport&);

  virtual void operator()(audio::transport::State);
  virtual void operator()(SampleTime t) { setTime(t); }
  virtual void operator()(const GuiSettings&);
  virtual void operator()(const widget::waveform::Viewport& vp) {
    setViewport(vp);
  }

  const SampleRangeVector timeSelection() const override {
    Lock l(lock());
    return timeSelection_;
  }

  SampleTime length() const { Lock l(lock()); return length_; }
  SampleTime time() const override { Lock l(lock()); return time_; }
  SampleTime requestedTime() const override {
    Lock l(lock());
    return requestedTime_;
  }

  void jumpToTime(SampleTime) override;
  void setLoopingSegment(int);

  void reset();

  const CriticalSection& lock() const { return getInstance()->lock_; }
  void zoomToCurrentTime() { zoomToTime(time()); }
  void zoomToTime(SampleTime);

 private:
  void zoomToCursor(SampleTime t);
  void setViewportProto(const widget::waveform::Viewport&);
  void checkTimeIsCloseToLoopPoint();

  SampleRangeVector timeSelection_;
  SampleTime time_;
  SampleTime requestedTime_;
  SampleTime length_;
  bool followCursor_;
  bool isDragging_;
  int loopingSegment_;
  bool timeIsCloseToLoopPoint_;

  widget::waveform::Viewport viewport_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentTime);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CURRENTTIME__
