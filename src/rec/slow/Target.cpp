#include "rec/slow/Target.h"
#include "rec/audio/Audio.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/Selections.h"
#include "rec/audio/source/Player.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

using rec::command::Command;
using thread::makeCallback;
using thread::functionCallback;

namespace {

}  // namespace

Target::Target(Instance* i) : TargetManager(i->window_), HasInstance(i) {}

void Target::addCommands() {
  add(Command::COPY, makeCallback(&copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.", 'c');

  add(Command::CUT, makeCallback(&cutToClipboard),
      "Cut", "Edit",
      "Copy the current selection to the clipboard and clear the selection.", 'x');

  add(Command::DEL, makeCallback(&cutNoClipboard),
      "Delete", "Edit",
      "Delete the current selection without changing the clipboard.", 'x');

  add(Command::PASTE, makeCallback(&pasteFromClipboard),
      "Paste", "Edit",
      "Replace the current selection with a copy of the clipboard.", 'v');

  // add(Command::CLEAR_NAVIGATOR,

  add(Command::OPEN, functionCallback(&gui::dialog::openOneFile,
                                      listeners()),
      "Open...", "File",
      "Open a dialog to select a new audio file for looping.", 'o');

  add(Command::SELECT_ALL, functionCallback(selectAll, instance_),
      "Select all", "Loops",
      "Select all of the file");

  add(Command::DESELECT_ALL, functionCallback(selectNone, instance_),
      "Select none", "Loops",
      "Select none of the file");


  add(Command::CLOSE_FILE, functionCallback(persist::setter<VirtualFile>(),
                                            VirtualFile()),
      "Close", "File",
      "Close the current file", 'w');

  add(Command::EJECT_CDS, makeCallback(&cd::ejectAll),
      "Eject All", "File",
      "Eject all CDs and DVDs");

  add(Command::ADD_LOOP_POINT, functionCallback(&addLoopPoint, instance_),
      "Add Loop Point", "Transport",
      "Add a loop point at the current time.");

  add(Command::TOGGLE_START_STOP, makeCallback(player(),
      &audio::source::Player::toggle),
      "Toggle Start/Stop", "Transport",
      "Start or pause", ' ');

  using gui::audio::Loops;
  Loops* loops = &components()->loops_;

  add(Command::CLEAR_LOOPS, makeCallback(loops, &Loops::clearLoops),
      "Clear Loops", "Loop",
      "Get rid of all loop points");

  add(Command::CLEAR_SELECTION, makeCallback(loops, &Loops::clearSelection),
      "Select None", "Loop",
      "Unselect all the loop points");

  add(Command::AUDIO_PREFERENCES, makeCallback(&device()->setupPage_,
                                               &gui::audio::SetupPage::show,
                                               &components()->mainPage_),
      "Audio Preferences...", "File",
      "Open the Audio Preferences pane.", ';');

#ifdef TODO

  add(Command::CLEAR_TIME, makeCallback(&instal, &MainPage::clearTime),
      "Clear Time Stretch", "Loop",
      "Clear all time and pitch shifting");
  add(Command::TREE_CLEAR, makeCallback(cc, &ComponentContainer::clearTree),
      "Clear Workspace", "Loop",
      "Remove all files and directories from the workspace area.");
  // add(Command::FILE_CLEAR, make, &ComponentContainer::clearFile);
#endif

#ifdef TODO
  // Causes a run-time error!
  add(Command::QUIT, makeCallback(JUCEApplication::getInstance(),
                                  &JUCEApplication::systemRequestedQuit),
      "Quit", "File",
      "Quit SlowGold", 'q');
#endif

  registerAllCommandsForTarget();
}

}  // namespace slow
}  // namespace rec

