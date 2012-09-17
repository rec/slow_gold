#ifndef __REC_SLOW_COMMANDS_ALLCOMMANDS__
#define __REC_SLOW_COMMANDS_ALLCOMMANDS__

// Created by the command line:
// new --include=command/Command.pb --proto=command::Commands src/rec/slow/commands/AllCommands.def

#include "rec/command/Command.pb.h"
#include "rec/util/proto/Defaulter.h"

namespace rec {
namespace slow {
namespace commands {

extern Def<command::Commands> allCommands;

}  // namespace commands
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_ALLCOMMANDS__
