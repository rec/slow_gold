#include "rec/slow/commands/KeyPresses.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands KeyPresses.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> keyPresses(
"command {\n"
  "  type: ADD_LOOP_POINT\n"
  "  keypress: \"return\"\n"
  "  keypress: \"command + =\"\n"
  "}\n"
  "command {\n"
  "  type: AUDIO_PREFERENCES\n"
  "  keypress: \"command + ;\"\n"
  "}\n"
  "command {\n"
  "  type: CLEAR_LOOPS\n"
  "  keypress: \"command + b\"\n"
  "}\n"
  "command {\n"
  "  type: CLOSE_FILE\n"
  "  keypress: \"command + w\"\n"
  "}\n"
  "command {\n"
  "  type: EJECT_CDS\n"
  "  keypress: \"command + e\"\n"
  "}\n"
  "command {\n"
  "  type: INVERT_LOOP_SELECTION\n"
  "  keypress: \"command + i\"\n"
  "}\n"
  "command {\n"
  "  type: KEYBOARD_MAPPINGS\n"
  "  keypress: \"command + k\"\n"
  "}\n"
  "command {\n"
  "  type: MIDI_MAPPINGS\n"
  "  keypress: \"command + m\"\n"
  "}\n"
  "command {\n"
  "  type: MUTE_VOLUME_TOGGLE\n"
  "  keypress: \".\"\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_VOLUME_DOWN\n"
  "  keypress: \"cursor down\"\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_VOLUME_UP\n"
  "  keypress: \"cursor up\"\n"
  "}\n"
  "command {\n"
  "  type: OPEN\n"
  "  keypress: \"command + o\"\n"
  "}\n"
  "command {\n"
  "  type: REDO\n"
  "  keypress: \"shift + command + z\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_START_STOP\n"
  "  keypress: \"spacebar\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_WHOLE_SONG_LOOP\n"
  "  keypress: \"command + t\"\n"
  "}\n"
  "command {\n"
  "  type: UNDO\n"
  "  keypress: \"command + z\"\n"
  "}\n"
  "command {\n"
  "  type: ZOOM_OUT\n"
  "  keypress: \"command + -\"\n"
  "}\n"
  "command {\n"
  "  type: ZOOM_OUT_FULL\n"
  "  keypress: \"command + shift + -\"\n"
  "}\n"
  "command {\n"
  "  type: ZOOM_TO_SELECTION\n"
  "  keypress: \"numpad *\"\n"
  "}\n"
  "command {\n"
  "  type: QUIT\n"
  "  keypress: \"command + q\"\n"
  "}\n"
  "command {\n"
  "  type: DEL\n"
  "  keypress: \"backspace\"\n"
  "  keypress: \"delete\"\n"
  "}\n"
  "command {\n"
  "  type: CUT\n"
  "  keypress: \"command + x\"\n"
  "}\n"
  "command {\n"
  "  type: COPY\n"
  "  keypress: \"command + c\"\n"
  "}\n"
  "command {\n"
  "  type: PASTE\n"
  "  keypress: \"command + v\"\n"
  "}\n"
  "command {\n"
  "  type: SELECT_ALL\n"
  "  keypress: \"command + a\"\n"
  "}\n"
  "command {\n"
  "  type: DESELECT_ALL\n"
  "  keypress: \"command + d\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 0\n"
  "  keypress: \"1\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 1\n"
  "  keypress: \"2\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 2\n"
  "  keypress: \"3\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 3\n"
  "  keypress: \"4\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 4\n"
  "  keypress: \"5\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 5\n"
  "  keypress: \"6\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 6\n"
  "  keypress: \"7\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 7\n"
  "  keypress: \"8\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 8\n"
  "  keypress: \"9\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 9\n"
  "  keypress: \"0\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: -5\n"
  "  keypress: \"command + cursor left\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: -4\n"
  "  keypress: \"cursor left\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: -2\n"
  "  keypress: \"cursor right\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: -1\n"
  "  keypress: \"command + cursor right\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 0\n"
  "  keypress: \"shift + !\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 1\n"
  "  keypress: \"shift + @\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 2\n"
  "  keypress: \"shift + #\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 3\n"
  "  keypress: \"shift + $\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 4\n"
  "  keypress: \"shift + %\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 5\n"
  "  keypress: \"shift + ^\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 6\n"
  "  keypress: \"shift + &\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 7\n"
  "  keypress: \"shift + *\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 8\n"
  "  keypress: \"shift + (\"\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 9\n"
  "  keypress: \"shift + )\"\n"
  "}\n"
  "command {\n"
  "  type: SELECT_ONLY\n"
  "  index: -5\n"
  "  keypress: \"ctrl + command + cursor left\"\n"
  "}\n"
  "command {\n"
  "  type: SELECT_ONLY\n"
  "  index: -4\n"
  "  keypress: \"ctrl + cursor left\"\n"
  "}\n"
  "command {\n"
  "  type: SELECT_ONLY\n"
  "  index: -2\n"
  "  keypress: \"ctrl + cursor right\"\n"
  "}\n"
  "command {\n"
  "  type: SELECT_ONLY\n"
  "  index: -1\n"
  "  keypress: \"ctrl + command + cursor right\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 0\n"
  "  keypress: \"command + 1\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 1\n"
  "  keypress: \"command + 2\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 2\n"
  "  keypress: \"command + 3\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 3\n"
  "  keypress: \"command + 4\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 4\n"
  "  keypress: \"command + 5\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 5\n"
  "  keypress: \"command + 6\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 6\n"
  "  keypress: \"command + 7\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 7\n"
  "  keypress: \"command + 8\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 8\n"
  "  keypress: \"command + 9\"\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 9\n"
  "  keypress: \"command + 0\"\n"
  "}\n"
  " "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
