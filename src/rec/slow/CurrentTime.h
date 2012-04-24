#ifndef __REC_SLOW_CURRENTTIME__
#define __REC_SLOW_CURRENTTIME__

#include "rec/base/Samples.h"
#include "rec/slow/HasInstance.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/block/Block.h"
#include "rec/data/DataListener.h"
#include "rec/util/Listener.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {
namespace slow {

class CurrentTime : public HasInstance,
                    public DataListener<widget::waveform::Viewport>,
                    public GlobalDataListener<GuiSettings>,
                    public Listener< Samples<44100> > {
 public:
  explicit CurrentTime(Instance* i);
  virtual ~CurrentTime() {}
  void init();

  void setTime(Samples<44100>);
  void setViewport(const widget::waveform::Viewport&);

  virtual void operator()(Samples<44100> t) { setTime(t); }
  virtual void operator()(const GuiSettings&);
  virtual void operator()(const widget::waveform::Viewport& vp) {
    setViewport(vp);
  }

  void setCursorTime(Samples<44100> time, int index, bool isTimeCursor);
  const block::BlockSet& timeSelection() const { return timeSelection_; }
  Samples<44100> length() const { Lock l(lock()); return length_; }
  Samples<44100> time() const { Lock l(lock()); return time_; }
  Samples<44100> requestedTime() const { Lock l(lock()); return requestedTime_; }
  void jumpToTime(Samples<44100> pos);

  void clear() { Lock l(lock()); time_ = 0; }

  const CriticalSection& lock() const { return instance_->lock_; }

 private:
  block::BlockSet timeSelection_;
  Samples<44100> time_;
  Samples<44100> requestedTime_;
  Samples<44100> zoomTime_;
  Samples<44100> length_;
  bool followCursor_;

  widget::waveform::Viewport viewport_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentTime);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CURRENTTIME__
