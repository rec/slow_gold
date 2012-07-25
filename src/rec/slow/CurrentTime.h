#ifndef __REC_SLOW_CURRENTTIME__
#define __REC_SLOW_CURRENTTIME__

#include "rec/audio/AudioSettings.pb.h"
#include "rec/base/SampleTime.h"
#include "rec/data/DataListener.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/Listener.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/range/Range.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace slow {

class CurrentTime : public HasInstance,
                    public DataListener<widget::waveform::Viewport>,
                    public GlobalDataListener<GuiSettings>,
                    public Listener<SampleTime> {
 public:
  explicit CurrentTime(Instance* i);
  virtual ~CurrentTime() {}

  void setTime(SampleTime);
  void setViewport(const widget::waveform::Viewport&);

  virtual void operator()(SampleTime t) { setTime(t); }
  virtual void operator()(const GuiSettings&);
  virtual void operator()(const widget::waveform::Viewport& vp) {
    setViewport(vp);
  }

  void setCursorTime(SampleTime time, int index, bool isTimeCursor);
  const SampleTimeVector timeSelection() const {
    Lock l(lock());
    return timeSelection_;
  }

  SampleTime length() const { Lock l(lock()); return length_; }
  SampleTime time() const { Lock l(lock()); return time_; }
  SampleTime requestedTime() const { Lock l(lock()); return requestedTime_; }
  void jumpToTime(SampleTime pos);

  void reset();

  const CriticalSection& lock() const { return instance_->lock_; }
  void zoomToCurrentTime() { zoomToTime(time()); }
  void zoomToTime(SampleTime);

 private:
  void zoomToCursor(SampleTime t);
  void setViewportProto(const widget::waveform::Viewport&);

  SampleTimeVector timeSelection_;
  SampleTime time_;
  SampleTime requestedTime_;
  SampleTime length_;
  bool followCursor_;
  bool isDragging_;

  widget::waveform::Viewport viewport_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentTime);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CURRENTTIME__
