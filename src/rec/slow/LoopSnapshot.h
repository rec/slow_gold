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
  SamplePosition length_;

  SampleSelection selection_;

  int selectionCount_;

  int segment_;

  typedef bool (*Function)(LoopSnapshot*);
  typedef std::map<command::Command::Type, LoopSnapshot::Function> Map;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LOOPSNAPSHOT__
