#ifndef __REC_SLOW_CURRENTTIME__
#define __REC_SLOW_CURRENTTIME__

#include "rec/base/Samples.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/block/Block.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/listener/DataListener.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace slow {

class CurrentTime : public HasInstance,
                    public DataListener<LoopPointList>,
                    public Listener< Samples<44100> > {
 public:
  CurrentTime(Instance* i) : HasInstance(i), time_(0), jumpToTime_(-1) {}

  virtual void operator()(Samples<44100> t) { ScopedLock l(lock_); time_ = t; }

  virtual void onDataChange(const LoopPointList&);

  void setCursorTime(int index, RealTime time);
  const block::BlockSet& timeSelection() const { return timeSelection_; }
  Samples<44100> time() const { Lock l(lock_); return time_; }
  Samples<44100> jumpToTime() const { Lock l(lock_); return jumpToTime_; }
  void setJumpToTime(Samples<44100> t) { Lock l(lock_); jumpToTime_ = t; }

  void clear() { Lock l(lock_); time_ = 0; }

 private:
  CriticalSection lock_;

  block::BlockSet timeSelection_;
  Samples<44100> time_;
  Samples<44100> jumpToTime_;

  DISALLOW_COPY_AND_ASSIGN(CurrentTime);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CURRENTTIME__
