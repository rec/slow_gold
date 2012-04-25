#include "rec/slow/commands/Commands.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands Commands.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> commands(
"command { type: ABOUT_THIS_PROGRAM category: \"(None)\"}\n"
  "command { type: ADD_LOOP_POINT category: \"Loops\"}\n"
  "command { type: AUDIO_PREFERENCES category: \"Audio\"}\n"
  "command { type: CHECK_FOR_UPDATES category: \"Help\" }\n"
  "command { type: CLEAR_LOOPS category: \"Loops\" }\n"
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
  "command { type: MODE_DRAG category: \"Edit\"}\n"
  "command { type: MODE_SET_TIME category: \"Edit\"}\n"
  "command { type: MODE_ZOOM_IN category: \"Edit\"}\n"
  "command { type: MODE_ADD_LOOP_POINT category: \"Edit\"}\n"
  "command { type: MUTE_VOLUME_TOGGLE category: \"Audio\"}\n"
  "command { type: NUDGE_VOLUME_DOWN category: \"Audio\"}\n"
  "command { type: NUDGE_VOLUME_UP category: \"Audio\"}\n"
  "command { type: OPEN category: \"File\"}\n"
  "command { type: OPEN_MANUAL category: \"Help\"}\n"
  "command { type: PASTE category: \"Edit\"}\n"
  "command { type: REDO category: \"Edit\"}\n"
  "command { type: RESET_GAIN_TO_UNITY category: \"Audio\"}\n"
  "command { type: REQUEST_SUPPORT category: \"Audio\"}\n"
  "command { type: SAVE_FILE category: \"File\"}\n"
  "command { type: SAVE_FILE_SELECTION category: \"File\"}\n"
  "command { type: SELECT_ALL category: \"Transport\"}\n"
  "command { type: TOGGLE_START_STOP category: \"Transport\"}\n"
  "command { type: TOGGLE_WHOLE_SONG_LOOP category: \"Selection\" }\n"
  "command { type: QUIT category: \"(None)\"}\n"
  "command { type: UNDO category: \"Edit\"}\n"
  "command { type: ZOOM_OUT category: \"Audio\"}\n"
  "command { type: ZOOM_OUT_FULL category: \"Audio\"}\n"
  "command { type: ZOOM_TO_SELECTION category: \"Audio\"}\n"
  " "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
