#ifndef __REC_SLOW_LOOPSNAPSHOT__
#define __REC_SLOW_LOOPSNAPSHOT__

#include <map>

#include "rec/util/LoopPoint.h"
#include "rec/command/Command.pb.h"

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

  typedef bool (*Function)(LoopSnapshot*);
  typedef command::Command::Type Command;
  typedef std::map<Command, LoopSnapshot::Function> Map;

  bool execute(Command, const Map&);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LOOPSNAPSHOT__
