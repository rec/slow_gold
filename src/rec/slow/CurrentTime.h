#ifndef __REC_SLOW_CURRENTTIME__
#define __REC_SLOW_CURRENTTIME__

#include "rec/base/Samples.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/block/Block.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace slow {

class CurrentTime : public HasInstance {
 public:
  explicit CurrentTime(Instance* i) : HasInstance(i) {}

  void jumpToTimeSelection(const LoopPointList&, Samples<44100> time);

  void setCursorTime(int index, RealTime time);
  const block::BlockSet& timeSelection() const { return timeSelection_; }

 private:
  block::BlockSet timeSelection_;

  DISALLOW_COPY_AND_ASSIGN(CurrentTime);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CURRENTTIME__
