#include "rec/command/data/Repeated.def.h"

// Created by the command line:
// new --include=command/Command --proto=Commands Repeated.def

namespace rec {
namespace command {
namespace data {

Def<Commands> repeated(
"command { type: JUMP index: 10 category: \"Transport\" }\n"
  "command { type: JUMP_SELECTED index: 10 category: \"Transport\" }\n"
  "command { type: SELECT index: 10 category: \"Selection\" }\n"
  "command { type: SELECT_ONLY index: 10 category: \"Selection\" }\n"
  "command { type: TOGGLE index: 10 category: \"Selection\" }\n"
  "command { type: UNSELECT index: 10 category: \"Selection\" }\n"
  "command { type: RECENT_FILES index: 64 category: \"File\" }\n"
  " "
);

}  // namespace data
}  // namespace command
}  // namespace rec
