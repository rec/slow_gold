#include "rec/command/data/Repeated.def.h"

// Created by the command line:
// new --include=command/Command --proto=Commands Repeated.def

namespace rec {
namespace command {
namespace data {

Def<Commands> repeated(
"command { type: CLEAR_LOOPS, index: 10, category: \"Selection\" } "
"command { type: DESELECT_ALL, index: 10, category: \"Selection\" } "
"command { type: INVERT_LOOP_SELECTION, index: 10, category: \"Selection\" } "
"command { type: JUMP, index: 10, category: \"Transport\" } "
"command { type: JUMP_SELECTED, index: 10, category: \"Transport\" } "
"command { type: SELECT, index: 10, category: \"Selection\" } "
"command { type: SELECT_ALL, index: 10, category: \"Selection\" } "
"command { type: SELECT_ONLY, index: 10, category: \"Selection\" } "
"command { type: TOGGLE, index: 10, category: \"Selection\" } "
"command { type: TOGGLE_WHOLE_SONG_LOOP, index: 10, category: \"Selection\" } "
"command { type: UNSELECT, index: 10, category: \"Selection\" } "
);

}  // namespace data
}  // namespace command
}  // namespace rec
