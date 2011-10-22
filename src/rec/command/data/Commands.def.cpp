#include "rec/command/data/Commands.def.h"

// Created by the command line:
// new --include=command/Command --proto=Commands Commands.def

namespace rec {
namespace command {
namespace data {

Def<Commands> commands(
"command { type: ADD_LOOP_POINT category: \"Selection\"}\n"
  "command { type: AUDIO_PREFERENCES category: \"Audio\"}\n"
  "command { type: CLEAR_LOOPS category: \"Selection\" }\n"
  "command { type: CLEAR_NAVIGATOR category: \"File\"}\n"
  "command { type: CLEAR_SAVED_FILE_DATA category: \"\"}\n"
  "command { type: CLOSE_FILE category: \"File\"}\n"
  "command { type: COPY category: \"Edit\"}\n"
  "command { type: CUT category: \"Edit\"}\n"
  "command { type: DEL category: \"Edit\"}\n"
  "command { type: DESELECT_ALL category: \"Select\"}\n"
  "command { type: DIM_VOLUME_TOGGLE category: \"Audio\"}\n"
  "command { type: EJECT_CDS category: \"File\"}\n"
  "command { type: INVERT_LOOP_SELECTION category: \"Selection\" }\n"
  "command { type: KEYBOARD_MAPPINGS category: \"File\"}\n"
  "command { type: MIDI_MAPPINGS category: \"File\"}\n"
  "command { type: MUTE_VOLUME_TOGGLE category: \"Audio\"}\n"
  "command { type: NUDGE_BEGIN_LEFT category: \"Selection\"}\n"
  "command { type: NUDGE_BEGIN_RIGHT category: \"Selection\"}\n"
  "command { type: NUDGE_END_LEFT category: \"Selection\"}\n"
  "command { type: NUDGE_END_RIGHT category: \"Selection\"}\n"
  "command { type: NUDGE_VOLUME_DOWN category: \"Selection\"}\n"
  "command { type: NUDGE_VOLUME_UP category: \"Selection\"}\n"
  "command { type: OPEN category: \"File\"}\n"
  "command { type: PASTE category: \"Edit\"}\n"
  "command { type: QUIT category: \"File\"}\n"
  "command { type: RECENT_FILES category: \"File\"}\n"
  "command { type: REDO category: \"Edit\"}\n"
  "command { type: RESET_GAIN_TO_UNITY category: \"Audio\"}\n"
  "command { type: SELECT_ALL category: \"Transport\"}\n"
  "command { type: TOGGLE_START_STOP category: \"Transport\"}\n"
  "command { type: TOGGLE_STRETCH_ENABLE category: \"Audio\"}\n"
  "command { type: TOGGLE_WHOLE_SONG_LOOP category: \"Selection\" }\n"
  "command { type: TREE_CLOSE category: \"\"}\n"
  "command { type: TREE_DOWN category: \"\"}\n"
  "command { type: TREE_LEFT category: \"\"}\n"
  "command { type: TREE_OPEN category: \"\"}\n"
  "command { type: TREE_RIGHT category: \"\"}\n"
  "command { type: TREE_UP category: \"\"}\n"
  "command { type: UNDO category: \"Edit\"}\n"
  "command { type: ZOOM_IN category: \"Audio\"}\n"
  "command { type: ZOOM_OUT category: \"Audio\"}\n"
  " "
);

}  // namespace data
}  // namespace command
}  // namespace rec
