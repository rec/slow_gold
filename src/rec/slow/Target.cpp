#include "rec/slow/Target.h"

#include "rec/audio/source/Player.h"
#include "rec/audio/Audio.h"
#include "rec/command/MidiCommandMapEditor.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/Selections.h"
#include "rec/slow/TargetCommands.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/Math.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

namespace {
}

using rec::command::Command;
using thread::methodCallback;
using thread::functionCallback;

Target::Target(Instance* i)
    : TargetManager(i->window_), HasInstance(i),
      midiCommandMap_(new command::MidiCommandMap(commandManager())) {
  device()->manager_.addMidiInputCallback("", midiCommandMap_.get());
  (*midiCommandMap_)(persist::get<command::CommandMapProto>());
}

Target::~Target() {
  device()->manager_.removeMidiInputCallback("", midiCommandMap_.get());
}

void Target::addCommands() {
  using gui::audio::Loops;
  Loops* loops = &components()->loops_;

  // Defined by Juce.
  add(Command::DEL, functionCallback(cutNoClipboard),
      "Delete", "Edit",
      "Delete the current selection without changing the clipboard.");

  add(Command::CUT, functionCallback(cutToClipboard),
      "Cut", "Edit",
      "Copy the current selection to the clipboard and clear the selection.",
      'x');

  add(Command::COPY, functionCallback(copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.", 'c');

  add(Command::PASTE, functionCallback(pasteFromClipboard),
      "Paste", "Edit",
      "Replace the current selection with a copy of the clipboard.", 'v');

  add(Command::SELECT_ALL, functionCallback(selectAll, instance_),
      "Select All", "Selection",
      "Select all of the file", 'a');

  add(Command::DESELECT_ALL, functionCallback(selectNone, instance_),
      "Select None", "Selection",
      "Select none of the file", 'd');

  //
  // REC commands!
  //
  add(Command::ADD_LOOP_POINT, functionCallback(&addLoopPoint, instance_),
      "Add Loop Point", "Loops",
      "Add a loop point at the current time.");

  add(Command::AUDIO_PREFERENCES, methodCallback(&device()->setupPage_,
                                                 &gui::audio::SetupPage::show,
                                                 &components()->mainPage_),
      "Audio Preferences...", "File",
      "Open the Audio Preferences pane.", ';');

  add(Command::CLEAR_NAVIGATOR, functionCallback(&clearNavigator),
      "Clear Navigator", "File",
      "Clear all files and directories from "
      "the navigator pane.");

  add(Command::CLEAR_LOOPS, methodCallback(loops, &Loops::clearLoops),
      "Clear Loops", "Loops",
      "Delete all loop points");

  add(Command::CLOSE_FILE, functionCallback(persist::setter<VirtualFile>(),
                                            VirtualFile()),
      "Close", "File",
      "Close the current file", 'w');

  add(Command::CONTRACT_FROM_NEXT_LOOP_POINT,
      functionCallback(&retractEnd, instance_),
      "Shrink From End", "Selection",
      "Disable the last loop segment");

  add(Command::CONTRACT_FROM_PREVIOUS_LOOP_POINT,
      functionCallback(&retractBegin, instance_),
      "Shrink From Start", "Selection",
      "Disable the first loop segment");

  add(Command::EJECT_CDS, functionCallback(&cd::ejectAll),
      "Eject All", "File",
      "Eject all CDs and DVDs", 'e');

  add(Command::INVERT_LOOP_SELECTION,
      functionCallback(selectInvert, instance_),
      "Invert Selection", "Selection",
      "Unselect everything selected and vice-versa.", 'i');

  add(Command::EXTEND_TO_NEXT_LOOP_POINT,
      functionCallback(&extendEnd, instance_),
      "Extend End", "Selection",
      "Enable the next segment in order.");

  add(Command::EXTEND_TO_PREVIOUS_LOOP_POINT,
      functionCallback(&extendBegin, instance_),
      "Extend Beginning", "Selection",
      "Enable the segment before the first one.");

  add(Command::JUMP_TO_NEXT_LOOP_POINT,
      functionCallback(&jumpToLoopPoint, instance_, 1),
      "Jump To Next", "Transport",
      "Immediately jump to the next loop point in the selected region.");

  add(Command::JUMP_TO_PREVIOUS_LOOP_POINT,
      functionCallback(&jumpToLoopPoint, instance_, -1),
      "Jump To Previous", "Transport",
      "Immediately jump to the previous loop point in the selected region.");

  add(Command::JUMP_TO_START,
      functionCallback(&jumpToStart, instance_),
      "Jump To Start", "Transport",
      "Jump to the beginning of the selected region.");

  add(Command::KEYBOARD_MAPPINGS,
      functionCallback(&keyboardMappings, instance_),
      "Edit Keyboard Mappings...", "File",
      "Edit keyboard mappings for commands.");

  add(Command::MIDI_MAPPINGS,
      functionCallback(&midiMappings, instance_),
      "Edit Midi Mappings...", "File",
      "Edit midi mappings for commands.");

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
      "NAME", "(None)",
      "Documentation");

  add(Command::NUDGE_VOLUME_UP,
      functionCallback(&nudgeVolumeUp, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::OPEN, functionCallback(&gui::dialog::openOneFile,
                                      listeners()),
      "Open...", "File",
      "Open a dialog to select a new audio file for looping.", 'o');

  add(Command::RECENT_FILES,
      functionCallback(recentFiles, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::SELECT_ONLY_0,
      functionCallback(selectItemOnly, instance_, 0),
      "Select Only Loop 1", "Selection",
      "Select loop 1 and unselect all other loops.");

  add(Command::SELECT_ONLY_1,
      functionCallback(&selectItemOnly, instance_, 1),
      "Select Only Loop 2", "Selection",
      "Select loop 2 and unselect all other loops.");

  add(Command::SELECT_ONLY_2,
      functionCallback(&selectItemOnly, instance_, 2),
      "Select Only Loop 3", "Selection",
      "Select loop 3 and unselect all other loops.");

  add(Command::SELECT_ONLY_3,
      functionCallback(&selectItemOnly, instance_, 3),
      "Select Only Loop 4", "Selection",
      "Select loop 4 and unselect all other loops.");

  add(Command::SELECT_ONLY_4,
      functionCallback(&selectItemOnly, instance_, 4),
      "Select Only Loop 5", "Selection",
      "Select loop 5 and unselect all other loops.");

  add(Command::SELECT_ONLY_5,
      functionCallback(&selectItemOnly, instance_, 5),
      "Select Only Loop 6", "Selection",
      "Select loop 6 and unselect all other loops.");

  add(Command::SELECT_ONLY_6,
      functionCallback(&selectItemOnly, instance_, 6),
      "Select Only Loop 7", "Selection",
      "Select loop 7 and unselect all other loops.");

  add(Command::SELECT_ONLY_7,
      functionCallback(&selectItemOnly, instance_, 7),
      "Select Only Loop 8", "Selection",
      "Select loop 8 and unselect all other loops.");

  add(Command::SELECT_ONLY_8,
      functionCallback(&selectItemOnly, instance_, 8),
      "Select Only Loop 9", "Selection",
      "Select loop 9 and unselect all other loops.");

  add(Command::SELECT_ONLY_9,
      functionCallback(&selectItemOnly, instance_, 9),
      "Select Only Loop 10", "Selection",
      "Select loop 10 and unselect all other loops.");

  add(Command::TOGGLE_0,
      functionCallback(&toggleItem, instance_, 0),
      "Toggle Loop 1", "Selection",
      "Toggle loop 1 between selected and unselected");

  add(Command::TOGGLE_1,
      functionCallback(&toggleItem, instance_, 1),
      "Toggle Loop 2", "Selection",
      "Toggle loop 2 between selected and unselected");

  add(Command::TOGGLE_2,
      functionCallback(&toggleItem, instance_, 2),
      "Toggle Loop 3", "Selection",
      "Toggle loop 3 between selected and unselected");

  add(Command::TOGGLE_3,
      functionCallback(&toggleItem, instance_, 3),
      "Toggle Loop 4", "Selection",
      "Toggle loop 4 between selected and unselected");

  add(Command::TOGGLE_4,
      functionCallback(&toggleItem, instance_, 4),
      "Toggle Loop 5", "Selection",
      "Toggle loop 5 between selected and unselected");

  add(Command::TOGGLE_5,
      functionCallback(&toggleItem, instance_, 5),
      "Toggle Loop 6", "Selection",
      "Toggle loop 6 between selected and unselected");

  add(Command::TOGGLE_6,
      functionCallback(&toggleItem, instance_, 6),
      "Toggle Loop 7", "Selection",
      "Toggle loop 7 between selected and unselected");

  add(Command::TOGGLE_7,
      functionCallback(&toggleItem, instance_, 7),
      "Toggle Loop 8", "Selection",
      "Toggle loop 8 between selected and unselected");

  add(Command::TOGGLE_8,
      functionCallback(&toggleItem, instance_, 8),
      "Toggle Loop 9", "Selection",
      "Toggle loop 9 between selected and unselected");

  add(Command::TOGGLE_9,
      functionCallback(&toggleItem, instance_, 9),
      "Toggle Loop 10", "Selection",
      "Toggle loop 10 between selected and unselected");

  add(Command::TOGGLE_WHOLE_SONG_LOOP,
      functionCallback(&toggleWholeSongLoop, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::TOGGLE_START_STOP,
      methodCallback(player(), &audio::source::Player::toggle),
      "Toggle Start/Stop", "Transport",
      "Start or pause", ' ');

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
      functionCallback(&unselectItem, instance_, 0),
      "Unselect Loop 1", "Selection",
      "Unselect loop 1 only");

  add(Command::UNSELECT_1,
      functionCallback(&unselectItem, instance_, 1),
      "Unselect Loop 2", "Selection",
      "Unselect loop 2 only");

  add(Command::UNSELECT_2,
      functionCallback(&unselectItem, instance_, 2),
      "Unselect Loop 3", "Selection",
      "Unselect loop 3 only");

  add(Command::UNSELECT_3,
      functionCallback(&unselectItem, instance_, 3),
      "Unselect Loop 4", "Selection",
      "Unselect loop 4 only");

  add(Command::UNSELECT_4,
      functionCallback(&unselectItem, instance_, 4),
      "Unselect Loop 5", "Selection",
      "Unselect loop 5 only");

  add(Command::UNSELECT_5,
      functionCallback(&unselectItem, instance_, 5),
      "Unselect Loop 6", "Selection",
      "Unselect loop 6 only");

  add(Command::UNSELECT_6,
      functionCallback(&unselectItem, instance_, 6),
      "Unselect Loop 7", "Selection",
      "Unselect loop 7 only");

  add(Command::UNSELECT_7,
      functionCallback(&unselectItem, instance_, 7),
      "Unselect Loop 8", "Selection",
      "Unselect loop 8 only");

  add(Command::UNSELECT_8,
      functionCallback(&unselectItem, instance_, 8),
      "Unselect Loop 9", "Selection",
      "Unselect loop 9 only");

  add(Command::UNSELECT_9,
      functionCallback(&unselectItem, instance_, 9),
      "Unselect Loop 10", "Selection",
      "Unselect loop 10 only");

  add(Command::ZOOM_IN,
      functionCallback(&zoomIn, instance_),
      "NAME", "(None)",
      "Documentation");

  add(Command::ZOOM_OUT,
      functionCallback(&zoomOut, instance_),
      "NAME", "(None)",
      "Documentation");

#ifdef TODO
  // Causes a run-time error!
  add(Command::QUIT, methodCallback(JUCEApplication::getInstance(),
                                  &JUCEApplication::systemRequestedQuit),
      "Quit", "File",
      "Quit SlowGold", 'q');
#endif

  registerAllCommandsForTarget();
}

}  // namespace slow
}  // namespace rec

