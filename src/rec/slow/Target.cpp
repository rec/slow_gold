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
void doNothing(Instance*) {}

void jumpToNextLoopPoint(Instance* i) {
}

void jumpToPreviousLoopPoint(Instance* i) {
}

void jumpToStart(Instance* i) {
}

void keyboardMappings(Instance* i) {
}

void nudgeBeginLeft(Instance* i) {
}

void nudgeBeginRight(Instance* i) {
}

void nudgeEndLeft(Instance* i) {
}

void nudgeEndRight(Instance* i) {
}

void nudgeVolumeDown(Instance* i) {
}

void nudgeVolumeUp(Instance* i) {
}

void recentFiles(Instance* i) {
}

void selectOnly0(Instance* i) {
}

void selectOnly1(Instance* i) {
}

void selectOnly2(Instance* i) {
}

void selectOnly3(Instance* i) {
}

void selectOnly4(Instance* i) {
}

void selectOnly5(Instance* i) {
}

void selectOnly6(Instance* i) {
}

void selectOnly7(Instance* i) {
}

void selectOnly8(Instance* i) {
}

void selectOnly9(Instance* i) {
}

void Toggle0(Instance* i) {
}

void Toggle1(Instance* i) {
}

void Toggle2(Instance* i) {
}

void Toggle3(Instance* i) {
}

void Toggle4(Instance* i) {
}

void Toggle5(Instance* i) {
}

void Toggle6(Instance* i) {
}

void Toggle7(Instance* i) {
}

void Toggle8(Instance* i) {
}

void Toggle9(Instance* i) {
}

void toggleWholeSongLoop(Instance* i) {
}

void toggleStartStop(Instance* i) {
}

void toggleStretchEnable(Instance* i) {
}

void treeClose(Instance* i) {
}

void treeDown(Instance* i) {
}

void treeLeft(Instance* i) {
}

void treeOpen(Instance* i) {
}

void treeRight(Instance* i) {
}

void treeUp(Instance* i) {
}

void Unselect0(Instance* i) {
}

void Unselect1(Instance* i) {
}

void Unselect2(Instance* i) {
}

void Unselect3(Instance* i) {
}

void Unselect4(Instance* i) {
}

void Unselect5(Instance* i) {
}

void Unselect6(Instance* i) {
}

void Unselect7(Instance* i) {
}

void Unselect8(Instance* i) {
}

void Unselect9(Instance* i) {
}

void zoomIn(Instance* i) {
}

void zoomOut(Instance* i) {
}

}  // namespace

Target::Target(Instance* i) : TargetManager(i->window_), HasInstance(i) {}

void Target::addCommands() {
  using gui::audio::Loops;
  Loops* loops = &components()->loops_;

  // Defined by Juce.
  add(Command::DEL, functionCallback(cutNoClipboard),
      "Delete", "Edit",
      "Delete the current selection without changing the clipboard.", 'x');

  add(Command::CUT, functionCallback(cutToClipboard),
      "Cut", "Edit",
      "Copy the current selection to the clipboard and clear the selection.", 'x');

  add(Command::COPY, functionCallback(copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.", 'c');

  add(Command::PASTE, functionCallback(pasteFromClipboard),
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

  add(Command::CONTRACT_FROM_NEXT_LOOP_POINT,
      functionCallback(&retractEnd, instance_),
      "Disable last segment", "Loops",
      "Disable the last loop segment");

  add(Command::CONTRACT_FROM_PREVIOUS_LOOP_POINT,
      functionCallback(&retractBegin, instance_),
      "Disable first segment", "Loops",
      "Disable the first loop segment");

  add(Command::EJECT_CDS, functionCallback(&cd::ejectAll),
      "Eject All", "File",
      "Eject all CDs and DVDs");

  add(Command::INVERT_LOOP_SELECTION,
      functionCallback(selectInvert, instance_),
      "Invert Selection", "Loops",
      "Unselect everything selected and vice-versa.");

  add(Command::EXTEND_TO_NEXT_LOOP_POINT,
      functionCallback(&extendEnd, instance_),
      "Enable next loop segment", "Loops",
      "Enable the next segment in order.");

  add(Command::EXTEND_TO_PREVIOUS_LOOP_POINT,
      functionCallback(&extendBegin, instance_),
      "Extend previous loop segment", "Loops",
      "Enable the segment before the first one.");

  add(Command::JUMP_TO_NEXT_LOOP_POINT,
      functionCallback(&jumpToNextLoopPoint, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::JUMP_TO_PREVIOUS_LOOP_POINT,
      functionCallback(&jumpToPreviousLoopPoint, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::JUMP_TO_START,
      functionCallback(&jumpToStart, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::KEYBOARD_MAPPINGS,
      functionCallback(&keyboardMappings, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::NUDGE_BEGIN_LEFT,
      functionCallback(&nudgeBeginLeft, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::NUDGE_BEGIN_RIGHT,
      functionCallback(&nudgeBeginRight, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::NUDGE_END_LEFT,
      functionCallback(&nudgeEndLeft, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::NUDGE_END_RIGHT,
      functionCallback(&nudgeEndRight, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::NUDGE_VOLUME_DOWN,
      functionCallback(&nudgeVolumeDown, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::NUDGE_VOLUME_UP,
      functionCallback(&nudgeVolumeUp, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::OPEN, functionCallback(&gui::dialog::openOneFile,
                                      listeners()),
      "Open...", "File",
      "Open a dialog to select a new audio file for looping.", 'o');

  add(Command::RECENT_FILES,
      functionCallback(&recentFiles, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_0,
      functionCallback(&selectOnly0, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_1,
      functionCallback(&selectOnly1, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_2,
      functionCallback(&selectOnly2, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_3,
      functionCallback(&selectOnly3, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_4,
      functionCallback(&selectOnly4, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_5,
      functionCallback(&selectOnly5, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_6,
      functionCallback(&selectOnly6, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_7,
      functionCallback(&selectOnly7, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_8,
      functionCallback(&selectOnly8, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_9,
      functionCallback(&selectOnly9, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_0,
      functionCallback(&Toggle0, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_1,
      functionCallback(&Toggle1, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_2,
      functionCallback(&Toggle2, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_3,
      functionCallback(&Toggle3, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_4,
      functionCallback(&Toggle4, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_5,
      functionCallback(&Toggle5, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_6,
      functionCallback(&Toggle6, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_7,
      functionCallback(&Toggle7, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_8,
      functionCallback(&Toggle8, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_9,
      functionCallback(&Toggle9, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_WHOLE_SONG_LOOP,
      functionCallback(&toggleWholeSongLoop, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_START_STOP,
      methodCallback(player(), &audio::source::Player::toggle),
      "Toggle Start/Stop", "Transport",
      "Start or pause", ' ');

  add(Command::TOGGLE_STRETCH_ENABLE,
      functionCallback(&toggleStretchEnable, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TREE_CLOSE,
      functionCallback(&treeClose, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TREE_DOWN,
      functionCallback(&treeDown, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TREE_LEFT,
      functionCallback(&treeLeft, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TREE_OPEN,
      functionCallback(&treeOpen, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TREE_RIGHT,
      functionCallback(&treeRight, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::TREE_UP,
      functionCallback(&treeUp, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_0,
      functionCallback(&Unselect0, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_1,
      functionCallback(&Unselect1, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_2,
      functionCallback(&Unselect2, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_3,
      functionCallback(&Unselect3, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_4,
      functionCallback(&Unselect4, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_5,
      functionCallback(&Unselect5, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_6,
      functionCallback(&Unselect6, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_7,
      functionCallback(&Unselect7, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_8,
      functionCallback(&Unselect8, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_9,
      functionCallback(&Unselect9, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::ZOOM_IN,
      functionCallback(&zoomIn, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::ZOOM_OUT,
      functionCallback(&zoomOut, instance_),
      "NAME", "Category",
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

