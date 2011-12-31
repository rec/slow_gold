#include "rec/slow/commands/Descriptions.def.h"

// Created by the command line:
// new --include=command/Command --proto=command::Commands src/rec/slow/commands/Descriptions.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> descriptions(
"command {\n"
  "  type: ADD_LOOP_POINT\n"
  "  desc {\n"
  "    menu: \"Add Loop Point At Current Time\"\n"
  "    full: \"Add a loop point at the current time.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: ABOUT_THIS_PROGRAM\n"
  "  desc {\n"
  "    menu: \"About SlowGold 8\"\n"
  "    full: \"Bring up a window describing SlowGold 8.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: AUDIO_PREFERENCES\n"
  "  desc {\n"
  "    menu: \"Audio Preferences...\"\n"
  "    full: \"Open the Audio Preferences pane.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CLEAR_LOOPS\n"
  "  desc {\n"
  "    menu: \"Clear Loops\"\n"
  "    full: \"Delete all loop points\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CLOSE_FILE\n"
  "  desc {\n"
  "    menu: \"Close\"\n"
  "    full: \"Close the current file\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: COPY\n"
  "  desc {\n"
  "    menu: \"Copy\"\n"
  "    full: \"Copy the current selection to the clipboard.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CUT\n"
  "  desc {\n"
  "    menu: \"Cut\"\n"
  "    full: \"Copy the current selection to the clipboard and clear the selection.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: DEL\n"
  "  desc {\n"
  "    menu: \"Delete\"\n"
  "    full: \"Delete the current selection without changing the clipboard.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: DESELECT_ALL\n"
  "  desc {\n"
  "    menu: \"Select None\"\n"
  "    full: \"Select none of the file\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: DIM_VOLUME_TOGGLE\n"
  "  desc {\n"
  "    menu: \"Toggle audio dim\"\n"
  "    full: \"Toggle audio dim on and off.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: EJECT_CDS\n"
  "  desc {\n"
  "    menu: \"Eject All\"\n"
  "    full: \"Eject all CDs and DVDs\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: INVERT_LOOP_SELECTION\n"
  "  desc {\n"
  "    menu: \"Invert Selection\"\n"
  "    full: \"Unselect everything selected and vice-versa.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: KEYBOARD_MAPPINGS\n"
  "  desc {\n"
  "    menu: \"Edit Keyboard Mappings...\"\n"
  "    full: \"Edit keyboard mappings for commands.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: MIDI_MAPPINGS\n"
  "  desc {\n"
  "    menu: \"Edit Midi Mappings...\"\n"
  "    full: \"Edit midi mappings for commands.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: MUTE_VOLUME_TOGGLE\n"
  "  desc {\n"
  "    menu: \"Toggle audio mute\"\n"
  "    full: \"Toggle audio mute on and off.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_VOLUME_DOWN\n"
  "  desc {\n"
  "    menu: \"Nudge gain down\"\n"
  "    full: \"Nudge gain down by 2dB\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_VOLUME_UP\n"
  "  desc {\n"
  "    menu: \"Nudge gain up\"\n"
  "    full: \"Nudge gain up by 2dB\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: OPEN\n"
  "  desc {\n"
  "    menu: \"Open...\"\n"
  "    full: \"Open a dialog to select a new audio file for looping.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: PASTE\n"
  "  desc {\n"
  "    menu: \"Paste\"\n"
  "    full: \"Replace the current selection with a copy of the clipboard.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: SELECT_ALL\n"
  "  desc {\n"
  "    menu: \"Select All\"\n"
  "    full: \"Select all of the file\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_COMMAND_BAR_AT_LEFT\n"
  "  desc {\n"
  "    menu: \"Command Bar At Left Side\"\n"
  "    full: \"Lay the Command Bar out on the left side of the Waveform Display.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_COMMAND_BAR_AT_TOP\n"
  "  desc {\n"
  "    menu: \"Command Bar At Top\"\n"
  "    full: \"Lay the Command Bar out on the top of the Waveform Display.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_MODES_AT_LEFT\n"
  "  desc {\n"
  "    menu: \"Modes At Left Side\"\n"
  "    full: \"Lay the Modes display out on the left side of the Waveform Display.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_MODES_AT_TOP\n"
  "  desc {\n"
  "    menu: \"Modes At Top\"\n"
  "    full: \"Lay the Modes display out on the top of the Waveform Display.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_FOLLOW_CURSOR\n"
  "  desc {\n"
  "    menu: \"Follow Cursor\"\n"
  "    full: \"Always keep the time cursor in the window.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_GRID_DISPLAY\n"
  "  desc {\n"
  "    menu: \"Show Time Gridlines\"\n"
  "    menu: \"Hide Time Gridlines\"\n"
  "    full: \"Toggle display of the time grid.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_PARALLEL_WAVEFORMS\n"
  "  desc {\n"
  "    menu: \"Show Stacked Waveform\"\n"
  "    menu: \"Show Parallel Waveforms\"\n"
  "    full: \"Toggle parallel/stacked waveform display.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_PREFADER_LEVELS\n"
  "  desc {\n"
  "    menu: \"Show Pre-Fader Levels\"\n"
  "    menu: \"Show Post-Fader levels\"\n"
  "    full: \"Toggle level display between pre- and post-fader.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_CURSOR_LABELS\n"
  "  desc {\n"
  "    menu: \"Show Loop Point Labels\"\n"
  "    menu: \"Hide Help Pane\"\n"
  "    full: \"Show draggable labels for the loop points on the waveform display.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_HELP_PANE\n"
  "  desc {\n"
  "    menu: \"Show Help Pane\"\n"
  "    menu: \"Hide Help Pane\"\n"
  "    full: \"Show help in help pane.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_LABELS_AT_TOP\n"
  "  desc {\n"
  "    menu: \"Show Loop Point Labels At Top\"\n"
  "    menu: \"Hide Help Pane\"\n"
  "    full: \"Show the loop point labels at the top of the waveform display.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_TOOLTIPS\n"
  "  desc {\n"
  "    menu: \"Show Tooltips\"\n"
  "    menu: \"Disable Tooltips\"\n"
  "    full: \"Show tooltips hovering over components.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_SELECTION_BUTTONS\n"
  "  desc {\n"
  "    menu: \"Show Loop Point Selection Buttons\"\n"
  "    menu: \"Hide Help Pane\"\n"
  "    full: \"Show help in help pane.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_TIMES_AT_TOP\n"
  "  desc {\n"
  "    menu: \"Show Grid Times At Top\"\n"
  "    menu: \"Hide Help Pane\"\n"
  "    full: \"Show the grid times for the grid at the top of the waveform display.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_STRETCH_ENABLE\n"
  "  desc {\n"
  "    menu: \"Enable Transforms\"\n"
  "    menu: \"Disable Transforms\"\n"
  "    full: \"Toggle pitch, time and stereo transforms of the sound.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: RESET_GAIN_TO_UNITY\n"
  "  desc {\n"
  "    menu: \"Reset Level\"\n"
  "    full: \"Reset audio level to 0 dB\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_WHOLE_SONG_LOOP\n"
  "  desc {\n"
  "    menu: \"Toggle Whole Segment Selection\"\n"
  "    full: \"Toggle selection between the current segment and the whole song.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_START_STOP\n"
  "  desc {\n"
  "    menu: \"Toggle Start/Stop\"\n"
  "    full: \"Start or pause\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: REDO\n"
  "  desc {\n"
  "    menu: \"Redo\"\n"
  "    full: \"Redoes a previously undone command.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: UNDO\n"
  "  desc {\n"
  "    menu: \"Undo\"\n"
  "    full: \"Undoes a previous command.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  desc {\n"
  "    menu: \"Jump To%s Selected Segment%s\"\n"
  "    full: \"Jump to the start of%s selected segment%s\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  desc {\n"
  "    menu: \"Jump To%s Segment%s\"\n"
  "    full: \"Jump to the start of%s segment%s\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: SELECT_ONLY\n"
  "  desc {\n"
  "    menu: \"Select%s Segment%s Only\"\n"
  "    full: \"Select%s segment%s only\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: QUIT\n"
  "  desc {\n"
  "    menu: \"Quit\"\n"
  "    full: \"Quit SlowGold\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: RECENT_FILES\n"
  "  desc {\n"
  "    full: \"Recent file %s%s\"\n"
  "    menu: \"Recent file %s%s\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: SELECT\n"
  "  desc {\n"
  "    menu: \"Select%s Segment%s\"\n"
  "    full: \"Select%s segment%s\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  desc {\n"
  "    menu: \"Toggle%s Segment%s Selection\"\n"
  "    full: \"Toggle%s segment%s between selected and unselected\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: UNSELECT\n"
  "  desc {\n"
  "    menu: \"Unselect%s Segment%s\"\n"
  "    full: \"Unselect%s segment%s\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: ZOOM_OUT\n"
  "  desc {\n"
  "    menu: \"Zoom Out\"\n"
  "    full: \"Zoom out.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: ZOOM_TO_SELECTION\n"
  "  desc {\n"
  "    menu: \"Zoom To Selection\"\n"
  "    full: \"Zoom to selection.\"\n"
  "  }\n"
  "}\n"
  " "
);

}  // namespace commands
}  // namespace slow
}  // namespace rec
