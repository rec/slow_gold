#include "rec/slow/Target.h"

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/command/MidiCommandMapEditor.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/LoopCommands.h"
#include "rec/slow/Model.h"
#include "rec/slow/Selections.h"
#include "rec/slow/TargetCommands.h"
#include "rec/util/Math.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

using thread::methodCallback;
using thread::functionCallback;

Target::Target(Instance* i)
    : HasInstance(i),
      targetManager_(i->window_),
      midiCommandMap_(new command::MidiCommandMap(targetManager_.commandManager())) {
  device()->manager_.addMidiInputCallback("", midiCommandMap_.get());
  (*midiCommandMap_)(persist::get<command::CommandMapProto>());
}

Target::~Target() {
  device()->manager_.removeMidiInputCallback("", midiCommandMap_.get());
}

void Target::add(CommandID c, const String& name,
                 const String& category, const String& desc) {
  add(c,
      functionCallback(&executeLoopCommand, instance_, static_cast<Command>(c)),
      name, category, desc);
}

void Target::addCommands() {
  using gui::audio::Loops;
  using rec::command::Command;

  // Defined by Juce.
  add(Command::DEL, functionCallback(cutNoClipboard),
      "Delete", "Edit",
      "Delete the current selection without changing the clipboard.");

  add(Command::CUT, functionCallback(cutToClipboard),
      "Cut", "Edit",
      "Copy the current selection to the clipboard and clear the selection.");

  add(Command::COPY, functionCallback(copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.");

  add(Command::PASTE, functionCallback(pasteFromClipboard),
      "Paste", "Edit",
      "Replace the current selection with a copy of the clipboard.");

  add(Command::SELECT_ALL,
      "Select All", "Selection",
      "Select all of the file");

  add(Command::DESELECT_ALL,
      "Select None", "Selection",
      "Select none of the file");

  //
  // REC commands!
  //
  add(Command::ADD_LOOP_POINT, functionCallback(&addLoopPoint, instance_),
      "Add Loop Point", "Loops",
      "Add a loop point at the current time.");

  add(Command::AUDIO_PREFERENCES, methodCallback(&device()->setupPage_,
                                                 &gui::audio::SetupPage::show,
                                                 &components()->mainPage_),
      "Audio Preferences...", "Audio",
      "Open the Audio Preferences pane.");

  add(Command::CLEAR_NAVIGATOR, functionCallback(&clearNavigator),
      "Clear Navigator", "File",
      "Clear all files and directories from "
      "the navigator pane.");

  add(Command::CLEAR_LOOPS,
      "Clear Loops", "Loops",
      "Delete all loop points");

  add(Command::CLOSE_FILE, functionCallback(persist::setter<VirtualFile>(),
                                            VirtualFile()),
      "Close", "File",
      "Close the current file");

  add(Command::DIM_VOLUME_TOGGLE,
      functionCallback(&dimVolumeToggle, instance_),
      "Toggle audio dim", "Audio",
      "Toggle audio dim on and off.");

  add(Command::EJECT_CDS, functionCallback(&cd::ejectAll),
      "Eject All", "File",
      "Eject all CDs and DVDs");

  add(Command::INVERT_LOOP_SELECTION,
      "Invert Selection", "Selection",
      "Unselect everything selected and vice-versa.");

  add(Command::JUMP_TO_NEXT_SEGMENT,
      "Jump To Next", "Transport",
      "Immediately jump to the next loop point and select it.");

  add(Command::JUMP_TO_PREVIOUS_SEGMENT,
      "Jump To Previous", "Transport",
      "Immediately jump to the previous segment and select it.");

  add(Command::JUMP_TO_LAST_SEGMENT,
      "Jump To Start", "Transport",
      "Jump to the first loop and select it.");

  add(Command::JUMP_TO_0,
      "Jump To Segment 0", "Transport",
      "Jump to segment 0 and select it.");

  add(Command::JUMP_TO_1,
      "Jump To Segment 1", "Transport",
      "Jump to segment 1 and select it.");

  add(Command::JUMP_TO_2,
      "Jump To Segment 2", "Transport",
      "Jump to segment 2 and select it.");

  add(Command::JUMP_TO_3,
      "Jump To Segment 3", "Transport",
      "Jump to segment 3 and select it.");

  add(Command::JUMP_TO_4,
      "Jump To Segment 4", "Transport",
      "Jump to segment 4 and select it.");

  add(Command::JUMP_TO_5,
      "Jump To Segment 5", "Transport",
      "Jump to segment 5 and select it.");

  add(Command::JUMP_TO_6,
      "Jump To Segment 6", "Transport",
      "Jump to segment 6 and select it.");

  add(Command::JUMP_TO_7,
      "Jump To Segment 7", "Transport",
      "Jump to segment 7 and select it.");

  add(Command::JUMP_TO_8,
      "Jump To Segment 8", "Transport",
      "Jump to segment 8 and select it.");

  add(Command::JUMP_TO_9,
      "Jump To Segment 9", "Transport",
      "Jump to segment 9 and select it.");

  add(Command::KEYBOARD_MAPPINGS,
      functionCallback(&keyboardMappings, instance_),
      "Edit Keyboard Mappings...", "File",
      "Edit keyboard mappings for commands.");

  add(Command::MIDI_MAPPINGS,
      functionCallback(&midiMappings, instance_),
      "Edit Midi Mappings...", "File",
      "Edit midi mappings for commands.");

  add(Command::MUTE_VOLUME_TOGGLE,
      functionCallback(&muteVolumeToggle, instance_),
      "Toggle audio mute", "Audio",
      "Toggle audio mute on and off.");

  add(Command::NUDGE_BEGIN_LEFT,
      functionCallback(&nudgeBeginLeft, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::NUDGE_BEGIN_RIGHT,
      functionCallback(&nudgeBeginRight, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::NUDGE_END_LEFT,
      functionCallback(&nudgeEndLeft, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::NUDGE_END_RIGHT,
      functionCallback(&nudgeEndRight, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::NUDGE_VOLUME_DOWN,
      functionCallback(&nudgeVolumeDown, instance_),
      "Nudge gain down", "Audio",
      "Nudge gain down by 2dB");

  add(Command::NUDGE_VOLUME_UP,
      functionCallback(&nudgeVolumeUp, instance_),
      "Nudge gain up", "Audio",
      "Nudge gain up by 2dB");

  add(Command::OPEN, functionCallback(&gui::dialog::openOneFile,
                                      listeners()),
      "Open...", "File",
      "Open a dialog to select a new audio file for looping.");

  add(Command::RESET_GAIN_TO_UNITY,
      functionCallback(resetGainToUnity, instance_),
      "Reset level", "Audio",
      "Reset audio level to 0 dB");

  add(Command::RECENT_FILES,
      functionCallback(recentFiles, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::SELECT_ONLY_0,
      "Select Only Loop 1", "Select Only",
      "Select loop 1 and unselect all other loops.");

  add(Command::SELECT_ONLY_1,
      "Select Only Loop 2", "Select Only",
      "Select loop 2 and unselect all other loops.");

  add(Command::SELECT_ONLY_2,
      "Select Only Loop 3", "Select Only",
      "Select loop 3 and unselect all other loops.");

  add(Command::SELECT_ONLY_3,
      "Select Only Loop 4", "Select Only",
      "Select loop 4 and unselect all other loops.");

  add(Command::SELECT_ONLY_4,
      "Select Only Loop 5", "Select Only",
      "Select loop 5 and unselect all other loops.");

  add(Command::SELECT_ONLY_5,
      "Select Only Loop 6", "Select Only",
      "Select loop 6 and unselect all other loops.");

  add(Command::SELECT_ONLY_6,
      "Select Only Loop 7", "Select Only",
      "Select loop 7 and unselect all other loops.");

  add(Command::SELECT_ONLY_7,
      "Select Only Loop 8", "Select Only",
      "Select loop 8 and unselect all other loops.");

  add(Command::SELECT_ONLY_8,
      "Select Only Loop 9", "Select Only",
      "Select loop 9 and unselect all other loops.");

  add(Command::SELECT_ONLY_9,
      "Select Only Loop 10", "Select Only",
      "Select loop 10 and unselect all other loops.");

  add(Command::SELECT_0,
      "Select Loop 1", "Select",
      "Select loop 1.");

  add(Command::SELECT_1,
      "Select Loop 2", "Select",
      "Select loop 2.");

  add(Command::SELECT_2,
      "Select Loop 3", "Select",
      "Select loop 3.");

  add(Command::SELECT_3,
      "Select Loop 4", "Select",
      "Select loop 4.");

  add(Command::SELECT_4,
      "Select Loop 5", "Select",
      "Select loop 5.");

  add(Command::SELECT_5,
      "Select Loop 6", "Select",
      "Select loop 6.");

  add(Command::SELECT_6,
      "Select Loop 7", "Select",
      "Select loop 7.");

  add(Command::SELECT_7,
      "Select Loop 8", "Select",
      "Select loop 8.");

  add(Command::SELECT_8,
      "Select Loop 9", "Select",
      "Select loop 9.");

  add(Command::SELECT_9,
      "Select Loop 10", "Select",
      "Select loop 10.");

  add(Command::TOGGLE_0,
      "Toggle Loop 1", "Select Toggle",
      "Toggle loop 1 between selected and unselected");

  add(Command::TOGGLE_1,
      "Toggle Loop 2", "Select Toggle",
      "Toggle loop 2 between selected and unselected");

  add(Command::TOGGLE_2,
      "Toggle Loop 3", "Select Toggle",
      "Toggle loop 3 between selected and unselected");

  add(Command::TOGGLE_3,
      "Toggle Loop 4", "Select Toggle",
      "Toggle loop 4 between selected and unselected");

  add(Command::TOGGLE_4,
      "Toggle Loop 5", "Select Toggle",
      "Toggle loop 5 between selected and unselected");

  add(Command::TOGGLE_5,
      "Toggle Loop 6", "Select Toggle",
      "Toggle loop 6 between selected and unselected");

  add(Command::TOGGLE_6,
      "Toggle Loop 7", "Select Toggle",
      "Toggle loop 7 between selected and unselected");

  add(Command::TOGGLE_7,
      "Toggle Loop 8", "Select Toggle",
      "Toggle loop 8 between selected and unselected");

  add(Command::TOGGLE_8,
      "Toggle Loop 9", "Select Toggle",
      "Toggle loop 9 between selected and unselected");

  add(Command::TOGGLE_9,
      "Toggle Loop 10", "Select Toggle",
      "Toggle loop 10 between selected and unselected");

  add(Command::TOGGLE_WHOLE_SONG_LOOP,
      "Toggle Whole Loop Selection", "Selection",
      "Toggle selection between the current segment and the whole song.");

  add(Command::TOGGLE_START_STOP,
      methodCallback(player(), &audio::source::Player::toggle),
      "Toggle Start/Stop", "Transport",
      "Start or pause");

  add(Command::TOGGLE_STRETCH_ENABLE,
      functionCallback(&toggleStretchEnable, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_CLOSE,
      functionCallback(&treeClose, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_DOWN,
      functionCallback(&treeDown, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_LEFT,
      functionCallback(&treeLeft, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_OPEN,
      functionCallback(&treeOpen, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_RIGHT,
      functionCallback(&treeRight, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TREE_UP,
      functionCallback(&treeUp, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::UNSELECT_0,
      "Unselect Loop 1", "Unselect",
      "Unselect loop 1 only");

  add(Command::UNSELECT_1,
      "Unselect Loop 2", "Unselect",
      "Unselect loop 2 only");

  add(Command::UNSELECT_2,
      "Unselect Loop 3", "Unselect",
      "Unselect loop 3 only");

  add(Command::UNSELECT_3,
      "Unselect Loop 4", "Unselect",
      "Unselect loop 4 only");

  add(Command::UNSELECT_4,
      "Unselect Loop 5", "Unselect",
      "Unselect loop 5 only");

  add(Command::UNSELECT_5,
      "Unselect Loop 6", "Unselect",
      "Unselect loop 6 only");

  add(Command::UNSELECT_6,
      "Unselect Loop 7", "Unselect",
      "Unselect loop 7 only");

  add(Command::UNSELECT_7,
      "Unselect Loop 8", "Unselect",
      "Unselect loop 8 only");

  add(Command::UNSELECT_8,
      "Unselect Loop 9", "Unselect",
      "Unselect loop 9 only");

  add(Command::UNSELECT_9,
      "Unselect Loop 10", "Unselect",
      "Unselect loop 10 only");

  add(Command::ZOOM_IN,
      functionCallback(&zoomIn, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::ZOOM_OUT,
      functionCallback(&zoomOut, instance_),
      "NAME", "(None)",
      "Documentation");

  targetManager()->registerAllCommandsForTarget();
}

}  // namespace slow
}  // namespace rec

