#include "rec/command/data/Descriptions.def.h"

namespace rec {
namespace command {
namespace data {

Def<Commands> descriptions(
"command { "
"  type: DEL, "
"  desc { "
"    menu=\"Delete\", "
"    full=\"Delete the current selection without changing the clipboard.\" "
"  } "
"} "
"command { "
"  type: CUT, "
"  desc { "
"    menu=\"Cut\", "
"    full=\"Copy the current selection to the clipboard and clear the selection.\" "
"  } "
"} "
"command { "
"  type: COPY, "
"  desc { "
"    menu=\"Copy\", "
"    full=\"Copy the current selection to the clipboard.\" "
"  } "
"} "
"command { "
"  type: PASTE, "
"  desc { "
"    menu=\"Paste\", "
"    full=\"Replace the current selection with a copy of the clipboard.\" "
"  } "
"} "
"command { "
"  type: SELECT_ALL, "
"  desc { "
"    menu=\"Select All\", "
"    full=\"Select all of the file\" "
"  } "
"} "
"command { "
"  type: DESELECT_ALL, "
"  desc { "
"    menu=\"Select None\", "
"    full=\"Select none of the file\" "
"  } "
"} "
"command { "
"  type: ADD_LOOP_POINT, "
"  desc { "
"    menu=\"Add Loop Point\", "
"    full=\"Add a loop point at the current time.\" "
"  } "
"} "
"command { "
"  type: AUDIO_PREFERENCES, "
"  desc { "
"    menu=\"Audio Preferences...\", "
"    full=\"Open the Audio Preferences pane.\" "
"  } "
"} "
"command { "
"  type: CLEAR_NAVIGATOR, "
"  desc { "
"    menu=\"Clear Navigator\", "
"    full=\"Clear all files and directories from \" "
"  } "
"} "
"command { "
"  type: CLEAR_LOOPS, "
"  desc { "
"    menu=\"Clear Loops\", "
"    full=\"Delete all loop points\" "
"  } "
"} "
"command { "
"  type: CLOSE_FILE, "
"  desc { "
"    menu=\"Close\", "
"    full=\"Close the current file\" "
"  } "
"} "
"command { "
"  type: DIM_VOLUME_TOGGLE, "
"  desc { "
"    menu=\"Toggle audio dim\", "
"    full=\"Toggle audio dim on and off.\" "
"  } "
"} "
"command { "
"  type: EJECT_CDS, "
"  desc { "
"    menu=\"Eject All\", "
"    full=\"Eject all CDs and DVDs\" "
"  } "
"} "
"command { "
"  type: INVERT_LOOP_SELECTION, "
"  desc { "
"    menu=\"Invert Selection\", "
"    full=\"Unselect everything selected and vice-versa.\" "
"  } "
"} "
"command { "
"  type: KEYBOARD_MAPPINGS, "
"  desc { "
"    menu=\"Edit Keyboard Mappings...\", "
"    full=\"Edit keyboard mappings for commands.\" "
"  } "
"} "
"command { "
"  type: MIDI_MAPPINGS, "
"  desc { "
"    menu=\"Edit Midi Mappings...\", "
"    full=\"Edit midi mappings for commands.\" "
"  } "
"} "
"command { "
"  type: MUTE_VOLUME_TOGGLE, "
"  desc { "
"    menu=\"Toggle audio mute\", "
"    full=\"Toggle audio mute on and off.\" "
"  } "
"} "
"command { "
"  type: NUDGE_VOLUME_DOWN, "
"  desc { "
"    menu=\"Nudge gain down\", "
"    full=\"Nudge gain down by 2dB\" "
"  } "
"} "
"command { "
"  type: NUDGE_VOLUME_UP, "
"  desc { "
"    menu=\"Nudge gain up\", "
"    full=\"Nudge gain up by 2dB\" "
"  } "
"} "
"command { "
"  type: OPEN, "
"  desc { "
"    menu=\"Open...\", "
"    full=\"Open a dialog to select a new audio file for looping.\" "
"  } "
"} "
"command { "
"  type: RESET_GAIN_TO_UNITY, "
"  desc { "
"    menu=\"Reset level\", "
"    full=\"Reset audio level to 0 dB\" "
"  } "
"} "
"command { "
"  type: TOGGLE_WHOLE_SONG_LOOP, "
"  desc { "
"    menu=\"Toggle Whole Segment Selection\", "
"    full=\"Toggle selection between the current segment and the whole song.\" "
"  } "
"} "
"command { "
"  type: TOGGLE_START_STOP, "
"  desc { "
"    menu=\"Toggle Start/Stop\", "
"    full=\"Start or pause\" "
"  } "
"} "
"command { "
"  type: UNDO, "
"  desc { "
"    menu=\"Undo\", "
"    full=\"Undoes a previous command.\" "
"  } "
"} "
" "
);

}  // namespace data
}  // namespace command
}  // namespace rec
