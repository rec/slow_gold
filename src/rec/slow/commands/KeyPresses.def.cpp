#include "rec/slow/commands/KeyPresses.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands src/rec/slow/commands/KeyPresses.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> keyPresses(
"command { type: ADD_LOOP_POINT  keypress: \"command + +\" }\n"
  "command { type: AUDIO_PREFERENCES  keypress: \"command + ;\" }\n"
  "command { type: CLEAR_LOOPS  keypress: \"command + b\" }\n"
  "command { type: CLOSE_FILE  keypress: \"command + w\" }\n"
  "command { type: COPY  keypress: \"command + c\" }\n"
  "command { type: CUT  keypress: \"command + x\" }\n"
  "command { type: DEL  keypress: \"backspace\"  keypress: \"delete\" }\n"
  "command { type: DESELECT_ALL  keypress: \"command + d\" }\n"
  "command { type: EJECT_CDS  keypress: \"command + e\" }\n"
  "command { type: INVERT_LOOP_SELECTION  keypress: \"command + i\" }\n"
  "command { type: KEYBOARD_MAPPINGS  keypress: \"command + k\" }\n"
  "command { type: MIDI_MAPPINGS  keypress: \"command + m\" }\n"
  "command { type: NUDGE_VOLUME_DOWN  keypress: \"cursor down\" }\n"
  "command { type: NUDGE_VOLUME_UP  keypress: \"cursor up\" }\n"
  "command { type: OPEN  keypress: \"command + o\" }\n"
  "command { type: PASTE  keypress: \"command + v\" }\n"
  "command { type: QUIT  keypress: \"command + q\" }\n"
  "command { type: REDO  keypress: \"shift + command + z\" }\n"
  "command { type: RESET_GAIN_TO_UNITY  keypress: \".\" }\n"
  "command { type: SELECT_ALL  keypress: \"command + a\" }\n"
  "command { type: TOGGLE_START_STOP  keypress: \"space\" }\n"
  "command { type: TOGGLE_START_STOP  keypress: \"spacebar\" }\n"
  "command { type: TOGGLE_WHOLE_SONG_LOOP  keypress: \"command + t\" }\n"
  "command { type: UNDO  keypress: \"command + z\" }\n"
  " "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
