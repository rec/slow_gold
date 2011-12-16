#include "rec/slow/commands/Repeated.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands src/rec/slow/commands/Repeated.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> repeated(
"command { type: JUMP index: 10 category: \"Transport\" }\n"
  "command { type: JUMP_SELECTED index: 10 category: \"Transport\" }\n"
  "command { type: SELECT index: 10 category: \"Selection\" }\n"
  "command { type: SELECT_ONLY index: 10 category: \"Selection\" }\n"
  "command { type: TOGGLE_SELECTION index: 10 category: \"Selection\" }\n"
  "command { type: UNSELECT index: 10 category: \"Selection\" }\n"
  "command { type: RECENT_FILES start_index: 0 index: 10 category: \"File\" }\n"
  " "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
