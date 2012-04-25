#include "rec/slow/commands/Repeated.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands Repeated.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> repeated(
"command { type: JUMP start_index: -5 index: 10 category: \"Transport\" }\n"
  "command { type: JUMP_SELECTED start_index: -5 index: 10 category: \"Transport\" }\n"
  "command { type: SELECT start_index: -5 index: 10 category: \"Selection\" }\n"
  "command { type: SELECT_ONLY start_index: -5 index: 10 category: \"Selection\" }\n"
  "command { type: TOGGLE_SELECTION start_index: -5 index: 10 category: \"Selection\" }\n"
  "command { type: UNSELECT start_index: -5 index: 10 category: \"Selection\" }\n"
  "command { type: RECENT_FILES start_index: 0 index: 10 category: \"File\" }\n"
  "command { type: SET_SAVE_FORMAT start_index: 0 index: 5 category: \"(None)\" } "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
