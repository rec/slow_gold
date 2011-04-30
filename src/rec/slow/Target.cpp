#include "rec/slow/Target.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/util/cd/Eject.h"

namespace rec {
namespace slow {

Target::Target(Instance* i) : TargetManager(&i->components_->mainPage_),
                              HasInstance(i) {
}

void Target::addCommands() {
  typedef rec::command::Command Command;
  using thread::makeCallback;

  add(Command::COPY, makeCallback(&copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.", 'c');

  add(Command::CUT, makeCallback(&cutToClipboard),
      "Cut", "Edit",
      "Copy the current selection to the clipboard and clear the selection.", 'x');

  using thread::functionCallback;
  add(Command::OPEN, functionCallback(&gui::dialog::openVirtualFile, listeners()),
      "Open...", "File",
      "Open dialog to select a new audio file for looping.", 'o');

  add(Command::EJECT, makeCallback(&cd::ejectAll),
      "Eject All", "File",
      "Eject all CDs and DVDs");

  add(Command::PASTE, makeCallback(&pasteFromClipboard),
      "Paste", "Edit",
      "Replace the current selection with a copy of the clipboard.", 'v');

  using gui::audio::Loops;
  Loops* loops = &components()->loops_;

  add(Command::CLEAR_LOOPS, makeCallback(loops, &Loops::clearLoops),
      "Clear Loops", "Loop",
      "Get rid of all loop points");

  add(Command::CLEAR_SELECTION, makeCallback(loops, &Loops::clearSelection),
      "Clear Selection", "Loop",
      "Unselect all the loop points");

  add(Command::CLOSE, functionCallback(persist::setter<VirtualFile>(),
                                       VirtualFile()),
      "Close", "File",
      "Close the current file", 'w');

#ifdef TODO
  add(Command::AUDIO_PREFERENCES, makeCallback(cc,
                                      &ComponentContainer::audioPreferences),
      "Audio Preferences...", "File",
      "Open the Audio Preferences pane.", ';');

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

