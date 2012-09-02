#ifndef __REC_SLOW_COMMANDS_ALLCOMMANDS__
#define __REC_SLOW_COMMANDS_ALLCOMMANDS__

// Created by the command line:
// new --include=command/Command --proto=command::Commands src/rec/slow/commands/AllCommands.def

#include "rec/command/Command.h"
#include "rec/util/proto/Defaulter.h"

namespace rec {
namespace slow {
namespace commands {

extern Def<command::Commands> allCommands;

}  // namespace commands
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_ALLCOMMANDS__
