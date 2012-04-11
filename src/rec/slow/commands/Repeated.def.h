#ifndef __REC_SLOW_COMMANDS_REPEATED__
#define __REC_SLOW_COMMANDS_REPEATED__

// Created by the command line:
// new --include=command/Command --proto=command::Commands Repeated.def

#include "rec/command/Command.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace slow {
namespace commands {

extern Def<command::Commands> repeated;

}  // namespace commands
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_REPEATED__
