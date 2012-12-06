#include "rec/slow/commands/AllCommands.def.h"

// Created by the command line:
// new --include=command/Command.pb --proto=command::Commands src/rec/slow/commands/AllCommands.def

namespace rec {
namespace slow {
namespace commands {

Def<command::Commands> allCommands(
"command {\n"
  "  type: ABOUT_THIS_PROGRAM\n"
  "  menu: \"Help\"\n"
  "  desc {\n"
  "    menu: \"About SlowGold 8\"\n"
  "    full: \"Bring up a window describing SlowGold 8.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: ADD_LOOP_POINT\n"
  "  menu: \"Loops\"\n"
  "  desc {\n"
  "    menu: \"Add Loop Point At Current Time\"\n"
  "    full: \"Add a loop point at the current time.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: AUDIO_PREFERENCES\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Audio Preferences...\"\n"
  "    full: \"Open the Audio Preferences pane.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CHECK_FOR_UPDATES\n"
  "  menu: \"Help\"\n"
  "  desc {\n"
  "    menu: \"Check For Updates\"\n"
  "    full: \"Check the World Wide Woodshed website for upgrades to SlowGold "
  "8.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CLEAR_ALL_SETTINGS\n"
  "  menu: \"Loops\"\n"
  "  desc {\n"
  "    menu: \"Clear All Settings And Quit\"\n"
  "    full: \"Clear all SlowGold settings for all tracks that have ever been "
  "visited and quit the program.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CLEAR_LOOPS\n"
  "  menu: \"Loops\"\n"
  "  desc {\n"
  "    menu: \"Clear Loops\"\n"
  "    full: \"Delete all loop points\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CLEAR_KEYBOARD_MAPPINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Clear Keyboard Mappings\"\n"
  "    full: \"Clear all keyboard command mappings to program default.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CLEAR_MIDI_MAPPINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Clear MIDI Mappings\"\n"
  "    full: \"Clear all MIDI command mappings.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CLEAR_SETTINGS_FOR_THIS_TRACK\n"
  "  menu: \"Loops\"\n"
  "  desc {\n"
  "    menu: \"Clear Settings For This Track And Quit\"\n"
  "    full: \"Clear all SlowGold settings for this track only and quit the "
  "program.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CLOSE_FILE\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Close\"\n"
  "    full: \"Close the current file\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: COPY\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Copy\"\n"
  "    full: \"Copy the current selection to the clipboard.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: COPY_ALL_LOOP_POINTS\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Copy All Loop Points\"\n"
  "    full: \"Copy both selected and unselected loop points to the "
  "clipboard.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: CUT\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Cut\"\n"
  "    full: \"Copy the current selection to the clipboard and clear the "
  "selection.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: DEL\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Delete\"\n"
  "    full: \"Delete the current selection without changing the "
  "clipboard.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: DESELECT_ALL\n"
  "  menu: \"Selection\"\n"
  "  desc {\n"
  "    menu: \"Select None\"\n"
  "    full: \"Select none of the file\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: DIM_VOLUME_TOGGLE\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Toggle audio dim\"\n"
  "    full: \"Toggle audio dim on and off.\"\n"
  " }\n"
  "}\n"
  "command {\n"
  "  type: EJECT_CDS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Eject All\"\n"
  "    full: \"Eject all CDs and DVDs\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: EXPORT_KEYBOARD_MAPPINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Export Keyboard Command Mappings...\"\n"
  "    full: \"Export keyboard command mappings.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: EXPORT_MIDI_MAPPINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Export MIDI Command Mappings...\"\n"
  "    full: \"Export MIDI command mappings.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: EXPORT_SETTINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Export SlowGold Settings...\"\n"
  "    full: \"Export all SlowGold Settings to a .zip file.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: IMPORT_KEYBOARD_MAPPINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Import Keyboard Command Mappings...\"\n"
  "    full: \"Import SlowGold keyboard command mappings.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: IMPORT_MIDI_MAPPINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Import MIDI Command Mappings\"\n"
  "    full: \"Import SlowGold MIDI command mappings.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: IMPORT_SETTINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Import SlowGold Settings...\"\n"
  "    full: \"Import SlowGold Settings from a .zip file and merge with "
  "current settings.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: INVERT_LOOP_SELECTION\n"
  "  menu: \"Selection\"\n"
  "  desc {\n"
  "    menu: \"Invert Selection\"\n"
  "    full: \"Unselect everything selected and vice-versa.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: JUMP\n"
  "  index: 9\n"
  "  menu: \"Transport\"\n"
  "  desc {\n"
  "    menu: \"Jump To First Segment\"\n"
  "    menu: \"Jump To Previous Segment\"\n"
  "    menu: \"Jump To Current Segment\"\n"
  "    menu: \"Jump To Next Segment\"\n"
  "    menu: \"Jump To Last Segment\"\n"
  "    menu: \"Jump To Segment 1\"\n"
  "    menu: \"Jump To Segment 2\"\n"
  "    menu: \"Jump To Segment 3\"\n"
  "    menu: \"Jump To Segment 4\"\n"
  "    menu: \"Jump To Segment 5\"\n"
  "    menu: \"Jump To Segment 6\"\n"
  "    menu: \"Jump To Segment 7\"\n"
  "    menu: \"Jump To Segment 8\"\n"
  "    menu: \"Jump To Segment 9\"\n"
  "    menu: \"Jump To Segment 10\"\n"
  "    full: \"Jump to the start of the first segment.\"\n"
  "    full: \"Jump to the start of the previous segment.\"\n"
  "    full: \"Jump to the start of the current segment.\"\n"
  "    full: \"Jump to the start of the next segment.\"\n"
  "    full: \"Jump to the start of the last segment.\"\n"
  "    full: \"Jump to the start of segment 1.\"\n"
  "    full: \"Jump to the start of segment 2.\"\n"
  "    full: \"Jump to the start of segment 3.\"\n"
  "    full: \"Jump to the start of segment 4.\"\n"
  "    full: \"Jump to the start of segment 5.\"\n"
  "    full: \"Jump to the start of segment 6.\"\n"
  "    full: \"Jump to the start of segment 7.\"\n"
  "    full: \"Jump to the start of segment 8.\"\n"
  "    full: \"Jump to the start of segment 9.\"\n"
  "    full: \"Jump to the start of segment 10.\"\n"
  "  }\n"
  "  start_index: -5\n"
  "}\n"
  "command {\n"
  "  type: JUMP_SELECTED\n"
  "  index: 9\n"
  "  menu: \"Transport\"\n"
  "  desc {\n"
  "    menu: \"Jump To First Selected Segment\"\n"
  "    menu: \"Jump To Previous Selected Segment\"\n"
  "    menu: \"Jump To Current Selected Segment\"\n"
  "    menu: \"Jump To Next Selected Segment\"\n"
  "    menu: \"Jump To Last Selected Segment\"\n"
  "    menu: \"Jump To Selected Segment 1\"\n"
  "    menu: \"Jump To Selected Segment 2\"\n"
  "    menu: \"Jump To Selected Segment 3\"\n"
  "    menu: \"Jump To Selected Segment 4\"\n"
  "    menu: \"Jump To Selected Segment 5\"\n"
  "    menu: \"Jump To Selected Segment 6\"\n"
  "    menu: \"Jump To Selected Segment 7\"\n"
  "    menu: \"Jump To Selected Segment 8\"\n"
  "    menu: \"Jump To Selected Segment 9\"\n"
  "    menu: \"Jump To Selected Segment 10\"\n"
  "    full: \"Jump To First Selected Segment\"\n"
  "    full: \"Jump To Previous Selected Segment\"\n"
  "    full: \"Jump To Current Selected Segment\"\n"
  "    full: \"Jump To Next Selected Segment\"\n"
  "    full: \"Jump To Last Selected Segment\"\n"
  "    full: \"Jump To Selected Segment 1\"\n"
  "    full: \"Jump To Selected Segment 2\"\n"
  "    full: \"Jump To Selected Segment 3\"\n"
  "    full: \"Jump To Selected Segment 4\"\n"
  "    full: \"Jump To Selected Segment 5\"\n"
  "    full: \"Jump To Selected Segment 6\"\n"
  "    full: \"Jump To Selected Segment 7\"\n"
  "    full: \"Jump To Selected Segment 8\"\n"
  "    full: \"Jump To Selected Segment 9\"\n"
  "    full: \"Jump To Selected Segment 10\"\n"
  "  }\n"
  "  start_index: -5\n"
  "}\n"
  "command {\n"
  "  type: LOOP_NEXT_SEGMENT\n"
  "  menu: \"Loops\"\n"
  "  desc {\n"
  "    menu: \"Loop Next Segment\"\n"
  "    full: \"Finish the current segment, then start looping the next "
  "segment.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: KEYBOARD_MAPPINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Edit Keyboard Mappings...\"\n"
  "    full: \"Edit keyboard mappings for commands.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: MIDI_MAPPINGS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Edit Midi Mappings...\"\n"
  "    full: \"Edit midi mappings for commands.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: MODE_ADD_LOOP_POINT\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Add Loop Point Mode\"\n"
  "    full: \"Enter Add Loop Point Mode, where clicking on the waveform adds "
  "a Loop Point at that location.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: MODE_DRAG\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Drag Mode\"\n"
  "    full: \"Enter drag mode, where you can drag the waveform back and "
  "forth.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: MODE_SET_TIME\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Set Time Mode\"\n"
  "    full: \"Enter Set Time Mode, where clicking in the waveform sets the "
  "time.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: MODE_ZOOM_IN\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Zoom In Mode\"\n"
  "    full: \"Enter Zoom In Mode, where clicking on the waveform zooms "
  "in.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: MUTE_VOLUME_TOGGLE\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Toggle audio mute\"\n"
  "    full: \"Toggle audio mute on and off.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_BACKWARD\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Nudge Backward\"\n"
  "    full: \"Nudge Backward One Segment Or 10 Seconds\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_FORWARD\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Nudge Forward\"\n"
  "    full: \"Nudge Forward One Segment Or 10 Seconds\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_VOLUME_DOWN\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Nudge volume down\"\n"
  "    full: \"Nudge volume down by 2dB\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_VOLUME_UP\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Nudge volume up\"\n"
  "    full: \"Nudge volume up by 2dB\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_SPEED_DOWN\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Nudge speed down\"\n"
  "    full: \"Nudge speed down\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: NUDGE_SPEED_UP\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Nudge speed up\"\n"
  "    full: \"Nudge speed up\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: OPEN\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Open...\"\n"
  "    full: \"Open a dialog to select a new audio file for looping.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: OPEN_MANUAL\n"
  "  menu: \"Help\"\n"
  "  desc {\n"
  "    menu: \"Download SlowGold 8 User Manual\"\n"
  "    full: \"Download the SlowGold 8 user manual from the World Wide "
  "Woodshed website.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: OPEN_PREVIOUS_FILE\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Re-Open Most Recent Closed File\"\n"
  "    full: \"Re-open the file that was most recently closed.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: OPEN_SLOWGOLD_DIRECTORY\n"
  "  menu: \"Help\"\n"
  "  desc {\n"
  "    menu: \"Open SlowGold Preferences Directory\"\n"
  "    full: \"Open the directory where all the SlowGold Preferences Files "
  "are located.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: PASTE\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Paste\"\n"
  "    full: \"Replace the current selection with a copy of the "
  "clipboard.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: PASTE_OVER_LOOP_POINTS\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Paste Over Loop Points\"\n"
  "    full: \"Replace all loop points with the loop points on the "
  "clipboard.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: QUIT\n"
  "  menu: \"(None)\"\n"
  "  desc {\n"
  "    menu: \"Quit\"\n"
  "    full: \"Quit SlowGold\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: RECENT_FILES\n"
  "  index: 32\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Recent file 1\"\n"
  "    menu: \"Recent file 2\"\n"
  "    menu: \"Recent file 3\"\n"
  "    menu: \"Recent file 4\"\n"
  "    menu: \"Recent file 5\"\n"
  "    menu: \"Recent file 6\"\n"
  "    menu: \"Recent file 7\"\n"
  "    menu: \"Recent file 8\"\n"
  "    menu: \"Recent file 9\"\n"
  "    menu: \"Recent file 10\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    menu: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "    full: \"Recent file\"\n"
  "  }\n"
  "  start_index: 0\n"
  "}\n"
  "command {\n"
  "  type: REDO\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Redo\"\n"
  "    full: \"Redoes a previously undone command.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: REQUEST_SUPPORT\n"
  "  menu: \"Help\"\n"
  "  desc {\n"
  "    menu: \"Request Technical Support\"\n"
  "    full: \"Make a request for technical support to World Wide "
  "Woodshed.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: RESET_GAIN_TO_UNITY\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Reset Volume\"\n"
  "    full: \"Reset volume to 0 dB\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: SAVE_FILE\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Save...\"\n"
  "    full: \"Save the full transformed file in the default save format.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: SAVE_FILE_SELECTION\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Save Selection...\"\n"
  "    full: \"Save just the selected portion of the transformed file in the "
  "default save format.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: SELECT\n"
  "  index: 10\n"
  "  menu: \"Selection\"\n"
  "  desc {\n"
  "    menu: \"Select First Segment\"\n"
  "    menu: \"Select Previous Segment\"\n"
  "    menu: \"Select Current Segment\"\n"
  "    menu: \"Select Next Segment\"\n"
  "    menu: \"Select Last Segment\"\n"
  "    menu: \"Select Segment 1\"\n"
  "    menu: \"Select Segment 2\"\n"
  "    menu: \"Select Segment 3\"\n"
  "    menu: \"Select Segment 4\"\n"
  "    menu: \"Select Segment 5\"\n"
  "    menu: \"Select Segment 6\"\n"
  "    menu: \"Select Segment 7\"\n"
  "    menu: \"Select Segment 8\"\n"
  "    menu: \"Select Segment 9\"\n"
  "    menu: \"Select Segment 10\"\n"
  "    full: \"Select First Segment\"\n"
  "    full: \"Select Previous Segment\"\n"
  "    full: \"Select Current Segment\"\n"
  "    full: \"Select Next Segment\"\n"
  "    full: \"Select Last Segment\"\n"
  "    full: \"Select Segment 1\"\n"
  "    full: \"Select Segment 2\"\n"
  "    full: \"Select Segment 3\"\n"
  "    full: \"Select Segment 4\"\n"
  "    full: \"Select Segment 5\"\n"
  "    full: \"Select Segment 6\"\n"
  "    full: \"Select Segment 7\"\n"
  "    full: \"Select Segment 8\"\n"
  "    full: \"Select Segment 9\"\n"
  "    full: \"Select Segment 10\"\n"
  "  }\n"
  "  start_index: -5\n"
  "}\n"
  "command {\n"
  "  type: SELECT_ALL\n"
  "  menu: \"Transport\"\n"
  "  desc {\n"
  "    menu: \"Select All\"\n"
  "    full: \"Select all of the file\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: SELECT_ONLY\n"
  "  index: -1\n"
  "  menu: \"Selection\"\n"
  "  desc {\n"
  "    menu: \"Select First Segment Only\"\n"
  "    menu: \"Select Previous Segment Only\"\n"
  "    menu: \"Select Current Segment Only\"\n"
  "    menu: \"Select Next Segment Only\"\n"
  "    menu: \"Select Last Segment Only\"\n"
  "    menu: \"Select Segment 1 Only\"\n"
  "    menu: \"Select Segment 2 Only\"\n"
  "    menu: \"Select Segment 3 Only\"\n"
  "    menu: \"Select Segment 4 Only\"\n"
  "    menu: \"Select Segment 5 Only\"\n"
  "    menu: \"Select Segment 6 Only\"\n"
  "    menu: \"Select Segment 7 Only\"\n"
  "    menu: \"Select Segment 8 Only\"\n"
  "    menu: \"Select Segment 9 Only\"\n"
  "    menu: \"Select Segment 10 Only\"\n"
  "    full: \"Select First Segment Only\"\n"
  "    full: \"Select Previous Segment Only\"\n"
  "    full: \"Select Current Segment Only\"\n"
  "    full: \"Select Next Segment Only\"\n"
  "    full: \"Select Last Segment Only\"\n"
  "    full: \"Select Segment 1 Only\"\n"
  "    full: \"Select Segment 2 Only\"\n"
  "    full: \"Select Segment 3 Only\"\n"
  "    full: \"Select Segment 4 Only\"\n"
  "    full: \"Select Segment 5 Only\"\n"
  "    full: \"Select Segment 6 Only\"\n"
  "    full: \"Select Segment 7 Only\"\n"
  "    full: \"Select Segment 8 Only\"\n"
  "    full: \"Select Segment 9 Only\"\n"
  "    full: \"Select Segment 10 Only\"\n"
  "  }\n"
  "  start_index: -5\n"
  "}\n"
  "command {\n"
  "  type: SET_SAVE_FORMAT\n"
  "  index: 4\n"
  "  menu: \"(None)\"\n"
  "  desc {\n"
  "    menu: \"AIFF\"\n"
  "    menu: \"FLAC\"\n"
  "    menu: \"Ogg Vorbis\"\n"
  "    menu: \"WAV\"\n"
  "    full: \"...\"\n"
  "    full: \"...\"\n"
  "    full: \"...\"\n"
  "    full: \"...\"\n"
  "  }\n"
  "  start_index: 0\n"
  "}\n"
  "command {\n"
  "  type: SET_LANGUAGE\n"
  "  index: 5\n"
  "  menu: \"(None)\"\n"
  "  desc {\n"
  "    menu: \"(None)\"\n"
  "    menu: \"German\"\n"
  "    menu: \"English\"\n"
  "    menu: \"Spanish\"\n"
  "    menu: \"French\"\n"
  "    menu: \"Indonesian\"\n"
  "    full: \"...\"\n"
  "    full: \"...\"\n"
  "    full: \"...\"\n"
  "    full: \"...\"\n"
  "    full: \"...\"\n"
  "    full: \"...\"\n"
  "  }\n"
  "  start_index: 0\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_ADVANCED_MENUS\n"
  "  menu: \"File\"\n"
  "  desc {\n"
  "    menu: \"Show Advanced Menus\"\n"
  "    full: \"Toggle show/hide of advanced menus.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"advanced_menus\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.slow.GuiSettings\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_AUTOMATIC_UPDATES\n"
  "  menu: \"Help\"\n"
  "  desc {\n"
  "    menu: \"Enable Automatic Updates\"\n"
  "    full: \"Enable or disable automatic updates of SlowGold 8.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"auto_check_for_updates\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.slow.GuiSettings\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_COMMAND_BAR_AT_LEFT\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Command Bar At Left Side\"\n"
  "    full: \"Lay the Command Bar out on the left side of the Waveform "
  "Display.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"command_bar_at_left\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_COMMAND_BAR_AT_TOP\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Command Bar At Top\"\n"
  "    full: \"Lay the Command Bar out on the top of the Waveform "
  "Display.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"command_bar_at_top\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_FILE_OPEN_TREE_DISPLAY\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Use Tree Display In File Save Dialog\"\n"
  "    full: \"Use Tree Display In File Save Dialog\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"use_tree_view_in_file_dialogs\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.slow.GuiSettings\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_FOLLOW_CURSOR\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Follow Cursor\"\n"
  "    full: \"Always keep the time cursor in the window.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"follow_cursor\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.slow.GuiSettings\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_GRID_DISPLAY\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Show Time Gridlines\"\n"
  "    full: \"Toggle display of the time grid.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"show_grid\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_MODES_AT_LEFT\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Modes At Left Side\"\n"
  "    full: \"Lay the Modes display out on the left side of the Waveform "
  "Display.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"modes_at_left\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_MODES_AT_TOP\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Modes At Top\"\n"
  "    full: \"Lay the Modes display out on the top of the Waveform "
  "Display.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"modes_at_top\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_PARALLEL_WAVEFORMS\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Show Stacked Waveform\"\n"
  "    full: \"Toggle parallel/stacked waveform display.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"parallel_waveforms\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_PREFADER_LEVELS\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Show Pre-Fader Levels\"\n"
  "    full: \"Toggle level display between pre- and post-fader.\"\n"
  "  }\n"
  "  setter {\n"
  "    is_global: false\n"
  "    address {\n"
  "      part {\n"
  "        name: \"prefader_levels\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.audio.Gain\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SELECTION\n"
  "  index: 9\n"
  "  menu: \"Selection\"\n"
  "  desc {\n"
  "    menu: \"Toggle First Segment Selection\"\n"
  "    menu: \"Toggle Previous Segment Selection\"\n"
  "    menu: \"Toggle Current Segment Selection\"\n"
  "    menu: \"Toggle Next Segment Selection\"\n"
  "    menu: \"Toggle Last Segment Selection\"\n"
  "    menu: \"Toggle Segment Selection 1\"\n"
  "    menu: \"Toggle Segment Selection 2\"\n"
  "    menu: \"Toggle Segment Selection 3\"\n"
  "    menu: \"Toggle Segment Selection 4\"\n"
  "    menu: \"Toggle Segment Selection 5\"\n"
  "    menu: \"Toggle Segment Selection 6\"\n"
  "    menu: \"Toggle Segment Selection 7\"\n"
  "    menu: \"Toggle Segment Selection 8\"\n"
  "    menu: \"Toggle Segment Selection 9\"\n"
  "    menu: \"Toggle Segment Selection 10\"\n"
  "    full: \"Toggle First Segment Selection\"\n"
  "    full: \"Toggle Previous Segment Selection\"\n"
  "    full: \"Toggle Current Segment Selection\"\n"
  "    full: \"Toggle Next Segment Selection\"\n"
  "    full: \"Toggle Last Segment Selection\"\n"
  "    full: \"Toggle Segment Selection 1\"\n"
  "    full: \"Toggle Segment Selection 2\"\n"
  "    full: \"Toggle Segment Selection 3\"\n"
  "    full: \"Toggle Segment Selection 4\"\n"
  "    full: \"Toggle Segment Selection 5\"\n"
  "    full: \"Toggle Segment Selection 6\"\n"
  "    full: \"Toggle Segment Selection 7\"\n"
  "    full: \"Toggle Segment Selection 8\"\n"
  "    full: \"Toggle Segment Selection 9\"\n"
  "    full: \"Toggle Segment Selection 10\"\n"
  "  }\n"
  "  start_index: -5\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP\n"
  "  menu: \"Help\"\n"
  "  desc {\n"
  "    menu: \"Show About Window At Startup\"\n"
  "    full: \"Toggle whether we show the About Window every time we start "
  "up.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"show_about_on_startup\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.slow.GuiSettings\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_CURSOR_LABELS\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Show Loop Point Labels\"\n"
  "    full: \"Show draggable labels for the loop points on the waveform "
  "display.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"show_cursor_labels\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_LABELS_AT_TOP\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Show Loop Point Labels At Top\"\n"
  "    full: \"Show the loop point labels at the top of the waveform "
  "display.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"show_labels_at_top\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_MASTER_TUNE\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Show Master Tune Slider\"\n"
  "    full: \"Show the Master Tune Slider in the Transform Panel.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"show_master_tune\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.slow.GuiSettings\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_SELECTION_BUTTONS\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Show Loop Point Selection Buttons\"\n"
  "    full: \"Show help in help pane.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"show_selection_buttons\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_SHOW_TIMES_AT_TOP\n"
  "  menu: \"Display\"\n"
  "  desc {\n"
  "    menu: \"Show Grid Times At Top\"\n"
  "    full: \"Show the grid times for the grid at the top of the waveform "
  "display.\"\n"
  "  }\n"
  "  setter {\n"
  "    address {\n"
  "      part {\n"
  "        name: \"show_times_at_top\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.widget.waveform.WaveformProto\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_START_STOP\n"
  "  menu: \"Transport\"\n"
  "  desc {\n"
  "    menu: \"Toggle Start/Stop\"\n"
  "    full: \"Start or pause\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_STRETCH_ENABLE\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Enable Stretch\"\n"
  "    full: \"Toggle between stretched and real-time playback.\"\n"
  "  }\n"
  "  setter {\n"
  "    is_global: false\n"
  "    address {\n"
  "      part {\n"
  "        name: \"time_enabled\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.audio.stretch.Stretch\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_TRANSFORM_ENABLE\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Enable Transforms\"\n"
  "    full: \"Toggle pitch, time and stereo transforms of the sound.\"\n"
  "  }\n"
  "  setter {\n"
  "    is_global: false\n"
  "    address {\n"
  "      part {\n"
  "        name: \"enabled\"\n"
  "      }\n"
  "    }\n"
  "    type_name: \"rec.audio.stretch.Stretch\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: TOGGLE_WHOLE_SONG_LOOP\n"
  "  menu: \"Selection\"\n"
  "  desc {\n"
  "    menu: \"Loop This Segment\"\n"
  "    full: \"Toggle selection between the current segment and the whole "
  "song.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: UNDO\n"
  "  menu: \"Edit\"\n"
  "  desc {\n"
  "    menu: \"Undo\"\n"
  "    full: \"Undoes a previous command.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: UNSELECT\n"
  "  index: 10\n"
  "  menu: \"Selection\"\n"
  "  desc {\n"
  "    menu: \"Unselect First Segment\"\n"
  "    menu: \"Unselect Previous Segment\"\n"
  "    menu: \"Unselect Current Segment\"\n"
  "    menu: \"Unselect Next Segment\"\n"
  "    menu: \"Unselect Last Segment\"\n"
  "    menu: \"Unselect Segment 1\"\n"
  "    menu: \"Unselect Segment 2\"\n"
  "    menu: \"Unselect Segment 3\"\n"
  "    menu: \"Unselect Segment 4\"\n"
  "    menu: \"Unselect Segment 5\"\n"
  "    menu: \"Unselect Segment 6\"\n"
  "    menu: \"Unselect Segment 7\"\n"
  "    menu: \"Unselect Segment 8\"\n"
  "    menu: \"Unselect Segment 9\"\n"
  "    menu: \"Unselect Segment 10\"\n"
  "    full: \"Unselect First Segment\"\n"
  "    full: \"Unselect Previous Segment\"\n"
  "    full: \"Unselect Current Segment\"\n"
  "    full: \"Unselect Next Segment\"\n"
  "    full: \"Unselect Last Segment\"\n"
  "    full: \"Unselect Segment 1\"\n"
  "    full: \"Unselect Segment 2\"\n"
  "    full: \"Unselect Segment 3\"\n"
  "    full: \"Unselect Segment 4\"\n"
  "    full: \"Unselect Segment 5\"\n"
  "    full: \"Unselect Segment 6\"\n"
  "    full: \"Unselect Segment 7\"\n"
  "    full: \"Unselect Segment 8\"\n"
  "    full: \"Unselect Segment 9\"\n"
  "    full: \"Unselect Segment 10\"\n"
  "  }\n"
  "  start_index: -5\n"
  "}\n"
  "command {\n"
  "  type: WHATS_NEW_PAGE\n"
  "  menu: \"Help\"\n"
  "  desc {\n"
  "    menu: \"What\\'s New In This Release?\"\n"
  "    full: \"Go to the webpage which tells you what new features and bug "
  "fixes are in the release you\\'re running.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: ZOOM_OUT\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Zoom Out\"\n"
  "    full: \"Zoom out.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: ZOOM_OUT_FULL\n"
  "  menu: \"Audio\"\n"
  "  desc {\n"
  "    menu: \"Zoom Out Completely\"\n"
  "    full: \"Zoom out as far as possible.\"\n"
  "  }\n"
  "}\n"
  "command {\n"
  "  type: ZOOM_TO_SELECTION\n"
  "  menu: \"Audio\"\n"
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
