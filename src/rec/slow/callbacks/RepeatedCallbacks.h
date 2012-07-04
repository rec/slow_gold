#ifndef __REC_SLOW_REPEATEDCALLBACKS__
#define __REC_SLOW_REPEATEDCALLBACKS__

#include "rec/command/Command.h"
#include "rec/command/CommandIDEncoder.h"

namespace rec {
namespace slow {

class Instance;
struct LoopSnapshot;

void addRepeatedCallbacks(command::CommandRecordTable*, Instance*, int repeat);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_REPEATEDCALLBACKS__
