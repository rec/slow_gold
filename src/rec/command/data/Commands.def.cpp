#include "rec/command/data/Commands.def.h"

// Created by the command line:
// new --include=command/Command --proto=Commands Commands.def

namespace rec {
namespace command {
namespace data {

Def<Commands> commands(
"command { type: ADD_LOOP_POINT category: \"Loops\"}\n"
  "command { type: AUDIO_PREFERENCES category: \"Audio\"}\n"
  "command { type: CLEAR_LOOPS category: \"Loops\" }\n"
  "command { type: CLEAR_NAVIGATOR category: \"File\"}\n"
  "command { type: CLOSE_FILE category: \"File\"}\n"
  "command { type: COPY category: \"Edit\"}\n"
  "command { type: CUT category: \"Edit\"}\n"
  "command { type: DEL category: \"Edit\"}\n"
  "command { type: DESELECT_ALL category: \"Selection\"}\n"
  "command { type: DIM_VOLUME_TOGGLE category: \"Audio\"}\n"
  "command { type: EJECT_CDS category: \"File\"}\n"
  "command { type: INVERT_LOOP_SELECTION category: \"Selection\" }\n"
  "command { type: KEYBOARD_MAPPINGS category: \"File\"}\n"
  "command { type: MIDI_MAPPINGS category: \"File\"}\n"
  "command { type: MUTE_VOLUME_TOGGLE category: \"Audio\"}\n"
  "command { type: NUDGE_VOLUME_DOWN category: \"Audio\"}\n"
  "command { type: NUDGE_VOLUME_UP category: \"Audio\"}\n"
  "command { type: OPEN category: \"File\"}\n"
  "command { type: PASTE category: \"Edit\"}\n"
  "command { type: REDO category: \"Edit\"}\n"
  "command { type: RESET_GAIN_TO_UNITY category: \"Audio\"}\n"
  "command { type: SELECT_ALL category: \"Transport\"}\n"
  "command { type: TOGGLE_START_STOP category: \"Transport\"}\n"
  "command { type: TOGGLE_WHOLE_SONG_LOOP category: \"Selection\" }\n"
  "command { type: QUIT category: \"Application\"}\n"
  "command { type: UNDO category: \"Edit\"}\n"
  " "
);

}  // namespace data
}  // namespace command
}  // namespace rec
