#ifndef __REC_SLOW_LOOPCOMMANDS__
#define __REC_SLOW_LOOPCOMMANDS__

#include "rec/command/Command.h"

namespace rec {
namespace slow {

class Instance;

bool executeLoopCommand(Instance*, command::Command::Type);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LOOPCOMMANDS__
