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
using command::Command;

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
      functionCallback(&executeLoopCommand, instance_, static_cast<Command::Type>(c)),
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

  add(Command::JUMP_TO_FIRST_SELECTED_SEGMENT,
      "Jump To First Selected Segment", "Transport",
      "Jump to the start of the first segment.");

  add(Command::JUMP_TO_NEXT_SELECTED_SEGMENT,
      "Jump To Next Selected Segment", "Transport",
      "Jump to the next segment and select it.");

  add(Command::JUMP_TO_PREVIOUS_SELECTED_SEGMENT,
      "Jump To Previous Selected Segment", "Transport",
      "Jump to the previous segment and select it.");

  add(Command::JUMP_TO_LAST_SELECTED_SEGMENT,
      "Jump To Last Selected Segment", "Transport",
      "Jump to the last segment in the selection.");


  add(Command::JUMP_TO_FIRST_SEGMENT,
      "Jump To First Segment", "Transport",
      "Jump to the start of the first segment.");

  add(Command::JUMP_TO_NEXT_SEGMENT,
      "Jump To Next Segment", "Transport",
      "Jump to the next segment and select it.");

  add(Command::JUMP_TO_PREVIOUS_SEGMENT,
      "Jump To Previous Segment", "Transport",
      "Jump to the previous segment and select it.");

  add(Command::JUMP_TO_LAST_SEGMENT,
      "Jump To Last Segment", "Transport",
      "Jump to the last segment and select it.");


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


  add(Command::SELECT_FIRST_SEGMENT_ONLY,
      "Select Only First Segment 1", "Select Only",
      "Select the first segment and unselect all other segments.");

  add(Command::SELECT_PREVIOUS_SEGMENT_ONLY,
      "Select Only Previous Segment 1", "Select Only",
      "Select the previous segment and unselect all other segments.");

  add(Command::SELECT_NEXT_SEGMENT_ONLY,
      "Select Only Next Segment 1", "Select Only",
      "Select the next segment and unselect all other segments.");

  add(Command::SELECT_LAST_SEGMENT_ONLY,
      "Select Only Last Segment 1", "Select Only",
      "Select the last segment and unselect all other segments.");


  add(Command::SELECT_ONLY_0,
      "Select Only Segment 1", "Select Only",
      "Select segment 1 and unselect all other segments.");

  add(Command::SELECT_ONLY_1,
      "Select Only Segment 2", "Select Only",
      "Select segment 2 and unselect all other segments.");

  add(Command::SELECT_ONLY_2,
      "Select Only Segment 3", "Select Only",
      "Select segment 3 and unselect all other segments.");

  add(Command::SELECT_ONLY_3,
      "Select Only Segment 4", "Select Only",
      "Select segment 4 and unselect all other segments.");

  add(Command::SELECT_ONLY_4,
      "Select Only Segment 5", "Select Only",
      "Select segment 5 and unselect all other segments.");

  add(Command::SELECT_ONLY_5,
      "Select Only Segment 6", "Select Only",
      "Select segment 6 and unselect all other segments.");

  add(Command::SELECT_ONLY_6,
      "Select Only Segment 7", "Select Only",
      "Select segment 7 and unselect all other segments.");

  add(Command::SELECT_ONLY_7,
      "Select Only Segment 8", "Select Only",
      "Select segment 8 and unselect all other segments.");

  add(Command::SELECT_ONLY_8,
      "Select Only Segment 9", "Select Only",
      "Select segment 9 and unselect all other segments.");

  add(Command::SELECT_ONLY_9,
      "Select Only Segment 10", "Select Only",
      "Select segment 10 and unselect all other segments.");

  add(Command::SELECT_0,
      "Select Segment 1", "Select",
      "Select segment 1.");

  add(Command::SELECT_1,
      "Select Segment 2", "Select",
      "Select segment 2.");

  add(Command::SELECT_2,
      "Select Segment 3", "Select",
      "Select segment 3.");

  add(Command::SELECT_3,
      "Select Segment 4", "Select",
      "Select segment 4.");

  add(Command::SELECT_4,
      "Select Segment 5", "Select",
      "Select segment 5.");

  add(Command::SELECT_5,
      "Select Segment 6", "Select",
      "Select segment 6.");

  add(Command::SELECT_6,
      "Select Segment 7", "Select",
      "Select segment 7.");

  add(Command::SELECT_7,
      "Select Segment 8", "Select",
      "Select segment 8.");

  add(Command::SELECT_8,
      "Select Segment 9", "Select",
      "Select segment 9.");

  add(Command::SELECT_9,
      "Select Segment 10", "Select",
      "Select segment 10.");

  add(Command::TOGGLE_0,
      "Toggle Segment 1", "Select Toggle",
      "Toggle segment 1 between selected and unselected");

  add(Command::TOGGLE_1,
      "Toggle Segment 2", "Select Toggle",
      "Toggle segment 2 between selected and unselected");

  add(Command::TOGGLE_2,
      "Toggle Segment 3", "Select Toggle",
      "Toggle segment 3 between selected and unselected");

  add(Command::TOGGLE_3,
      "Toggle Segment 4", "Select Toggle",
      "Toggle segment 4 between selected and unselected");

  add(Command::TOGGLE_4,
      "Toggle Segment 5", "Select Toggle",
      "Toggle segment 5 between selected and unselected");

  add(Command::TOGGLE_5,
      "Toggle Segment 6", "Select Toggle",
      "Toggle segment 6 between selected and unselected");

  add(Command::TOGGLE_6,
      "Toggle Segment 7", "Select Toggle",
      "Toggle segment 7 between selected and unselected");

  add(Command::TOGGLE_7,
      "Toggle Segment 8", "Select Toggle",
      "Toggle segment 8 between selected and unselected");

  add(Command::TOGGLE_8,
      "Toggle Segment 9", "Select Toggle",
      "Toggle segment 9 between selected and unselected");

  add(Command::TOGGLE_9,
      "Toggle Segment 10", "Select Toggle",
      "Toggle segment 10 between selected and unselected");

  add(Command::TOGGLE_WHOLE_SONG_LOOP,
      "Toggle Whole Segment Selection", "Selection",
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
      "Unselect Segment 1", "Unselect",
      "Unselect segment 1");

  add(Command::UNSELECT_1,
      "Unselect Segment 2", "Unselect",
      "Unselect segment 2");

  add(Command::UNSELECT_2,
      "Unselect Segment 3", "Unselect",
      "Unselect segment 3");

  add(Command::UNSELECT_3,
      "Unselect Segment 4", "Unselect",
      "Unselect segment 4");

  add(Command::UNSELECT_4,
      "Unselect Segment 5", "Unselect",
      "Unselect segment 5");

  add(Command::UNSELECT_5,
      "Unselect Segment 6", "Unselect",
      "Unselect segment 6");

  add(Command::UNSELECT_6,
      "Unselect Segment 7", "Unselect",
      "Unselect segment 7");

  add(Command::UNSELECT_7,
      "Unselect Segment 8", "Unselect",
      "Unselect segment 8");

  add(Command::UNSELECT_8,
      "Unselect Segment 9", "Unselect",
      "Unselect segment 9");

  add(Command::UNSELECT_9,
      "Unselect Segment 10", "Unselect",
      "Unselect segment 10");

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

