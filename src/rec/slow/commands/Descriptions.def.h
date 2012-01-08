#ifndef __REC_SLOW_COMMANDS_DESCRIPTIONS__
#define __REC_SLOW_COMMANDS_DESCRIPTIONS__

// Created by the command line:
// new --include=command/Command --proto=command::Commands Descriptions.def

#include "rec/command/Command.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace slow {
namespace commands {

extern Def<command::Commands> descriptions;

}  // namespace commands
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMMANDS_DESCRIPTIONS__
