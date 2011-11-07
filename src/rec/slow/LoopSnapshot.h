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
  Samples<44100> time_;
  Samples<44100> length_;

  block::BlockSet selection_;

  int selectionCount_;

  int segment_;

  typedef bool (*Function)(LoopSnapshot*);
  typedef std::map<int32, LoopSnapshot::Function> Map;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LOOPSNAPSHOT__
