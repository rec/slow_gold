#ifndef __REC_SLOW_LOOPCOMMANDS__
#define __REC_SLOW_LOOPCOMMANDS__

#include "rec/command/Command.h"

namespace rec {
namespace slow {

typedef command::Command::Type Command;

class Instance;

bool executeLoopCommand(Instance*, Command);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LOOPCOMMANDS__
