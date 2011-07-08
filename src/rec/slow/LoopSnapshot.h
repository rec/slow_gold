#ifndef __REC_SLOW_LOOPSNAPSHOT__
#define __REC_SLOW_LOOPSNAPSHOT__

#include <map>

#include "rec/slow/LoopCommands.h"
#include "rec/util/LoopPoint.h"

namespace rec {
namespace slow {

class Instance;

struct LoopSnapshot {
  LoopSnapshot() {}
  LoopSnapshot(Instance*);

  Instance* instance_;
  LoopPointList loops_;
  SamplePosition time_;
  SampleSelection selection_;

  int loopSize_;
  int selectionCount_;

  int segment_;
  int previous_;
  int next_;
  int last_;

  typedef bool (*Function)(LoopSnapshot*);
  typedef std::map<Command, LoopSnapshot::Function> Map;

  bool execute(Command, const Map&);

  // Limit x to [0, loopSize_).
  int limit(int x) {
  	if (!loopSize_)
      return 0;
    for (; x >= loopSize_; x -= loopSize_);
    for (; x < 0; x += loopSize_);
    return x;
  }
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LOOPSNAPSHOT__
