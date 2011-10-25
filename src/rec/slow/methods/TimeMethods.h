#ifndef __REC_SLOW_METHODS_TIMEMETHODS__
#define __REC_SLOW_METHODS_TIMEMETHODS__

#include "rec/base/Samples.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/block/Block.h"

namespace rec {
namespace slow {
namespace methods {

class TimeMethods : public HasInstance {
 public:
  explicit TimeMethods(Instance* i) : HasInstance(i) {}

  void jumpToTimeSelection(const block::BlockSet& ts, Samples<44100> time);
  void setCursorTime(int index, RealTime time, const VirtualFile& f);

 private:
  DISALLOW_COPY_AND_ASSIGN(TimeMethods);
};

}  // namespace methods
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_METHODS_TIMEMETHODS__
