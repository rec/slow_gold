#include "rec/command/data/Repeated.def.h"

// Created by the command line:
// new --include=command/Command --proto=Commands Repeated.def

namespace rec {
namespace command {
namespace data {

Def<Commands> repeated(
"command { type: CLEAR_LOOPS, category: \"Selection\" } "
"command { type: DESELECT_ALL, category: \"Selection\" } "
"command { type: INVERT_LOOP_SELECTION, category: \"Selection\" } "
"command { type: JUMP, category: \"Transport\" } "
"command { type: JUMP_SELECTED, category: \"Transport\" } "
"command { type: SELECT, category: \"Selection\" } "
"command { type: SELECT_ALL, category: \"Selection\" } "
"command { type: SELECT_ONLY, category: \"Selection\" } "
"command { type: TOGGLE, category: \"Selection\" } "
"command { type: TOGGLE_WHOLE_SONG_LOOP, category: \"Selection\" } "
"command { type: UNSELECT, category: \"Selection\" } "
);

}  // namespace data
}  // namespace command
}  // namespace rec
