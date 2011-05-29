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


void jumpToLoopPoint(Instance* i, int offset) {
  LoopPointList loops(i->model_->loopPointList());
  SampleTime time = i->player_->getNextReadPosition();
  int j = 0, size = loops.loop_point_size();
  for (; j < size && time >= loops.loop_point(j).time(); ++j);
  j = std::min(size - 1, std::max(0, j + offset));
  i->model_->setTriggerTime(loops.loop_point(j).time());
}

void jumpToStart(Instance* i) {
  i->model_->setTriggerTime(0);
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
      functionCallback(&jumpToLoopPoint, instance_, 1),
      "NAME", "Category",
      "Documentation");

  add(Command::JUMP_TO_PREVIOUS_LOOP_POINT,
      functionCallback(&jumpToLoopPoint, instance_, -1),
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
      functionCallback(recentFiles, instance_),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_0,
      functionCallback(selectItemOnly, instance_, 0),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_1,
      functionCallback(&selectItemOnly, instance_, 1),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_2,
      functionCallback(&selectItemOnly, instance_, 2),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_3,
      functionCallback(&selectItemOnly, instance_, 3),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_4,
      functionCallback(&selectItemOnly, instance_, 4),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_5,
      functionCallback(&selectItemOnly, instance_, 5),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_6,
      functionCallback(&selectItemOnly, instance_, 6),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_7,
      functionCallback(&selectItemOnly, instance_, 7),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_8,
      functionCallback(&selectItemOnly, instance_, 8),
      "NAME", "Category",
      "Documentation");

  add(Command::SELECT_ONLY_9,
      functionCallback(&selectItemOnly, instance_, 9),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_0,
      functionCallback(&toggleItem, instance_, 0),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_1,
      functionCallback(&toggleItem, instance_, 1),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_2,
      functionCallback(&toggleItem, instance_, 2),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_3,
      functionCallback(&toggleItem, instance_, 3),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_4,
      functionCallback(&toggleItem, instance_, 4),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_5,
      functionCallback(&toggleItem, instance_, 5),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_6,
      functionCallback(&toggleItem, instance_, 6),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_7,
      functionCallback(&toggleItem, instance_, 7),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_8,
      functionCallback(&toggleItem, instance_, 8),
      "NAME", "Category",
      "Documentation");

  add(Command::TOGGLE_9,
      functionCallback(&toggleItem, instance_, 9),
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
      functionCallback(&unselectItem, instance_, 0),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_1,
      functionCallback(&unselectItem, instance_, 1),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_2,
      functionCallback(&unselectItem, instance_, 2),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_3,
      functionCallback(&unselectItem, instance_, 3),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_4,
      functionCallback(&unselectItem, instance_, 4),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_5,
      functionCallback(&unselectItem, instance_, 5),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_6,
      functionCallback(&unselectItem, instance_, 6),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_7,
      functionCallback(&unselectItem, instance_, 7),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_8,
      functionCallback(&unselectItem, instance_, 8),
      "NAME", "Category",
      "Documentation");

  add(Command::UNSELECT_9,
      functionCallback(&unselectItem, instance_, 9),
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

