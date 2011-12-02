#ifndef __REC_SLOW_CURRENTTIME__
#define __REC_SLOW_CURRENTTIME__

#include "rec/base/Samples.h"
#include "rec/slow/HasInstance.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/block/Block.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/DataListener.h"
#include "rec/util/Listener.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

class CurrentTime : public HasInstance,
                    public DataListener<LoopPointList>,
                    public DataListener<widget::waveform::ZoomProto>,
                    public GlobalDataListener<GuiSettings>,
                    public Listener< Samples<44100> > {
 public:
  explicit CurrentTime(Instance* i);
  virtual ~CurrentTime() {}

  virtual void operator()(Samples<44100> t);
  virtual void onDataChange(const LoopPointList&);
  virtual void onDataChange(const GuiSettings&);
  virtual void onDataChange(const widget::waveform::ZoomProto&);

  void setCursorTime(int index, Samples<44100> time);
  const block::BlockSet& timeSelection() const { return timeSelection_; }
  Samples<44100> time() const { Lock l(lock_); return time_; }
  Samples<44100> jumpTime() const { Lock l(lock_); return jumpTime_; }
  void jumpToTime(Samples<44100> pos);

  void clear() { Lock l(lock_); time_ = 0; }

 private:
  CriticalSection lock_;

  block::BlockSet timeSelection_;
  Samples<44100> time_;
  Samples<44100> jumpTime_;
  Samples<44100> zoomTime_;
  Samples<44100> length_;
  bool followCursor_;
  widget::waveform::ZoomProto zoom_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentTime);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CURRENTTIME__
