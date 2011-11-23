#ifndef __REC_SLOW_LOOPSNAPSHOT__
#define __REC_SLOW_LOOPSNAPSHOT__

#include <map>

#include "rec/util/LoopPoint.h"

namespace rec {
namespace slow {

class Instance;

struct LoopSnapshot {
  LoopSnapshot() {}
  LoopSnapshot(Instance*);

  Instance* instance_;
  LoopPointList loops_;

  typedef bool (*Function)(LoopSnapshot*);
  typedef std::map<int32, LoopSnapshot::Function> Map;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(LoopSnapshot);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LOOPSNAPSHOT__
