#ifndef __REC_SLOW_COMMANDS_SETTERS__
#define __REC_SLOW_COMMANDS_SETTERS__

// Created by the command line:
// new --include=command/Command --proto=command::Commands src/rec/slow/commands/Setters.def

#include "rec/command/Command.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace slow {
namespace commands {

extern Def<command::Commands> setters;

}  // namespace commands
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_SETTERS__
