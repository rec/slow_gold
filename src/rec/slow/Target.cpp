#include "rec/slow/Target.h"
#include "rec/audio/Audio.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/Selections.h"
#include "rec/audio/source/Player.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/Math.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

using rec::command::Command;
using thread::methodCallback;
using thread::functionCallback;

namespace {

void clearNavigator() { persist::set(VirtualFileList()); }
void doNothing() {}

}  // namespace

Target::Target(Instance* i) : TargetManager(i->window_), HasInstance(i) {}

void Target::addCommands() {
  using gui::audio::Loops;
  Loops* loops = &components()->loops_;

  // Defined by Juce.
  add(Command::DEL, functionCallback(cutNoClipboard),
      "Delete", "Edit",
      "Delete the current selection without changing the clipboard.", 'x');

  add(Command::CUT, functionCallback(&cutToClipboard),
      "Cut", "Edit",
      "Copy the current selection to the clipboard and clear the selection.", 'x');

  add(Command::COPY, functionCallback(&copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.", 'c');

  add(Command::PASTE, functionCallback(&pasteFromClipboard),
      "Paste", "Edit",
      "Replace the current selection with a copy of the clipboard.", 'v');

  add(Command::SELECT_ALL, functionCallback(selectAll, instance_),
      "Select all", "Loops",
      "Select all of the file");

  add(Command::DESELECT_ALL, functionCallback(selectNone, instance_),
      "Select none", "Loops",
      "Select none of the file");

  //
  // REC commands!
  //
  add(Command::ADD_LOOP_POINT, functionCallback(&addLoopPoint, instance_),
      "Add Loop Point", "Transport",
      "Add a loop point at the current time.");

  add(Command::AUDIO_PREFERENCES, methodCallback(&device()->setupPage_,
                                               &gui::audio::SetupPage::show,
                                               &components()->mainPage_),
      "Audio Preferences...", "File",
      "Open the Audio Preferences pane.", ';');

  add(Command::CLEAR_NAVIGATOR, functionCallback(&clearNavigator),
      "Clear Navigator", "Navigator", "Clear all files and directories from "
      "the navigator pane.");

  add(Command::CLEAR_LOOPS, methodCallback(loops, &Loops::clearLoops),
      "Clear Loops", "Loop",
      "Delete all loop points");

  // TODO:  this needs to move to the new metaphor...!
  add(Command::CLEAR_SELECTION, methodCallback(loops, &Loops::clearSelection),
      "Select None", "Loop",
      "Unselect all the loop points");

  add(Command::CLOSE_FILE, functionCallback(persist::setter<VirtualFile>(),
                                            VirtualFile()),
      "Close", "File",
      "Close the current file", 'w');

  add(Command::CONTRACT_FROM_NEXT_LOOP_POINT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::CONTRACT_FROM_PREVIOUS_LOOP_POINT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::EJECT_CDS, functionCallback(&cd::ejectAll),
      "Eject All", "File",
      "Eject all CDs and DVDs");

  add(Command::INVERT_LOOP_SELECTION, functionCallback(selectInvert, instance_),
      "Invert Selection", "Loops",
      "Unselect everything selected and vice-versa.");

  add(Command::EXTEND_TO_NEXT_LOOP_POINT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::EXTEND_TO_PREVIOUS_LOOP_POINT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::JUMP_TO_NEXT_LOOP_POINT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::JUMP_TO_PREVIOUS_LOOP_POINT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::JUMP_TO_START, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::KEYBOARD_MAPPINGS, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::NUDGE_BEGIN_LEFT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::NUDGE_BEGIN_RIGHT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::NUDGE_END_LEFT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::NUDGE_END_RIGHT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::NUDGE_VOLUME_DOWN, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::NUDGE_VOLUME_UP, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::OPEN, functionCallback(&gui::dialog::openOneFile,
                                      listeners()),
      "Open...", "File",
      "Open a dialog to select a new audio file for looping.", 'o');

  add(Command::RECENT_FILES, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_0, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_1, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_2, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_3, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_4, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_5, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_6, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_7, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_8, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_9, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_0, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_1, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_2, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_3, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_4, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_5, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_6, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_7, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_8, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_9, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_WHOLE_SONG_LOOP, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TOGGLE_START_STOP, methodCallback(player(),
      &audio::source::Player::toggle),
      "Toggle Start/Stop", "Transport",
      "Start or pause", ' ');

  add(Command::TOGGLE_STRETCH_ENABLE, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TREE_CLOSE, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TREE_DOWN, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TREE_LEFT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TREE_OPEN, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TREE_RIGHT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::TREE_UP, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_0, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_1, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_2, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_3, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_4, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_5, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_6, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_7, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_8, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::UNSELECT_9, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::ZOOM_IN, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

  add(Command::ZOOM_OUT, functionCallback(&doNothing),
      "Name", "Category",
      "Documentation");

#ifdef TODO

  add(Command::CLEAR_TIME, methodCallback(&instal, &MainPage::clearTime),
      "Clear Time Stretch", "Loop",
      "Clear all time and pitch shifting");
  add(Command::TREE_CLEAR, methodCallback(cc, &ComponentContainer::clearTree),
      "Clear Workspace", "Loop",
      "Remove all files and directories from the workspace area.");
  // add(Command::FILE_CLEAR, make, &ComponentContainer::clearFile);

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

