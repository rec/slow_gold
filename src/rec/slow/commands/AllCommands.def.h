#ifndef __REC_SLOW_COMMANDS_ALLCOMMANDS__
#define __REC_SLOW_COMMANDS_ALLCOMMANDS__

// Created by the command line:
// new --include=command/Command --proto=command::Commands AllCommands.def

#include "rec/command/Command.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace slow {
namespace commands {

extern Def<command::Commands> allCommands;

}  // namespace commands
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_ALLCOMMANDS__
