#ifndef __REC_SLOW_COMMANDS_COMMANDS__
#define __REC_SLOW_COMMANDS_COMMANDS__

// Created by the command line:
// new --include=command/Command --proto=command::Commands Commands.def

#include "rec/command/Command.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace slow {
namespace commands {

extern Def<command::Commands> commands;

}  // namespace commands
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_COMMANDS__
