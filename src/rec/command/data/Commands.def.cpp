#include "rec/command/data/Commands.def.h"

namespace rec {
namespace command {
namespace data {

Def<Commands> commands(
"command { type: ADD_LOOP_POINT, category: \"Loops\"} "
"command { type: AUDIO_PREFERENCES, category: \"Audio\"} "
"command { type: CLEAR_LOOPS, category: \"Loops\"} "
"command { type: CLEAR_NAVIGATOR, category: \"File\"} "
"command { type: CLEAR_SAVED_FILE_DATA, category: \"\"} "
"command { type: CLOSE_FILE, category: \"File\"} "
"command { type: COPY, category: \"Edit\"} "
"command { type: CUT, category: \"Edit\"} "
"command { type: DEL, category: \"Edit\"} "
"command { type: DESELECT_ALL, category: \"Select\"} "
"command { type: DIM_VOLUME_TOGGLE, category: \"Audio\"} "
"command { type: EJECT_CDS, category: \"File\"} "
"command { type: INVERT_LOOP_SELECTION, category: \"Loops\"} "
"command { type: JUMP, category: \"Transport\"} "
"command { type: JUMP_SELECTED, category: \"Transport\"} "
"command { type: KEYBOARD_MAPPINGS, category: \"File\"} "
"command { type: MIDI_MAPPINGS, category: \"File\"} "
"command { type: MUTE_VOLUME_TOGGLE, category: \"Audio\"} "
"command { type: NUDGE_BEGIN_LEFT, category: \"\"} "
"command { type: NUDGE_BEGIN_RIGHT, category: \"\"} "
"command { type: NUDGE_END_LEFT, category: \"\"} "
"command { type: NUDGE_END_RIGHT, category: \"\"} "
"command { type: NUDGE_VOLUME_DOWN, category: \"\"} "
"command { type: NUDGE_VOLUME_UP, category: \"\"} "
"command { type: OPEN, category: \"File\"} "
"command { type: PASTE, category: \"Edit\"} "
"command { type: QUIT, category: \"File\"} "
"command { type: RECENT_FILES, category: \"File\"} "
"command { type: REDO, category: \"Edit\"} "
"command { type: RESET_GAIN_TO_UNITY, category: \"Audio\"} "
"command { type: SELECT, category: \"Transport\"} "
"command { type: SELECT_ALL, category: \"Transport\"} "
"command { type: SELECT_ONLY, category: \"Transport\"} "
"command { type: TOGGLE, category: \"Transport\"} "
"command { type: TOGGLE_START_STOP, category: \"Transport\"} "
"command { type: TOGGLE_STRETCH_ENABLE, category: \"Audio\"} "
"command { type: TOGGLE_WHOLE_SONG_LOOP, category: \"Selection\"} "
"command { type: TREE_CLOSE, category: \"\"} "
"command { type: TREE_DOWN, category: \"\"} "
"command { type: TREE_LEFT, category: \"\"} "
"command { type: TREE_OPEN, category: \"\"} "
"command { type: TREE_RIGHT, category: \"\"} "
"command { type: TREE_UP, category: \"\"} "
"command { type: UNDO, category: \"Edit\"} "
"command { type: UNSELECT, category: \"Selection\"} "
"command { type: ZOOM_IN, category: \"\"} "
"command { type: ZOOM_OUT, category: \"\"} "
);

}  // namespace data
}  // namespace command
}  // namespace rec
