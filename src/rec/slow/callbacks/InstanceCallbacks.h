#ifndef __REC_SLOW_TARGETCOMMANDS__
#define __REC_SLOW_TARGETCOMMANDS__

#include "rec/command/Command.h"

namespace rec {
namespace slow {

class Instance;

void addInstanceCallbacks(command::CommandRecordTable*, Instance*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_TARGETCOMMANDS__
