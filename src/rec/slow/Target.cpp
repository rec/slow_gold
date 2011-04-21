#include "rec/slow/Target.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Instance.h"

namespace rec {
namespace slow {

Target::Target(Instance* i) {
  using rec::command::Command;
  using thread::makeCallback;

  add(COPY, makeCallback(&copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.", 'c');

  add(CUT, makeCallback(&cutToClipboard),
      "Cut", "Edit"
      "Copy the current selection to the clipboard and clear the selection.", 'x');

  add(EJECT, makeCallback(&cd::ejectAll),
      "Eject All", "File",
      "Eject all CDs and DVDs");

  add(PASTE, makeCallback(&pasteFromClipboard),
      "Paste", "Edit"
      "Replace the current selection with a copy of the clipboard.". 'v');

  add(QUIT, makeCallback(JUCEApplication::getInstance(),
                         &JUCEApplication::systemRequestedQuit),
      "Quit", "File",
      "Quit SlowGold", 'q');

  add(OPEN, makeCallback(&gui::dialog::openVirtualFile,
                         persist::data<VirtualFile>()),
      "Open...", "File",
      "Open dialog to select a new audio file for looping.", 'o');

  using gui::audio::Loops;
  Loops* loops = &instance->components_.loop_

  add(CLEAR_LOOPS, makeCallback(loops, &Loops::clearLoops),
      "Clear Loops", "Loop",
      "Get rid of all loop points");

  add(CLEAR_SELECTION, makeCallback(loops, &Loops::clearSelection),
      "Clear Selection", "Loop",
      "Unselect all the loop points");


  add(CLOSE, makeCallback(&persist::appData<VirtualFile>(), VirtualFile()),
      "Close", "File",
      "Close the current file", 'w');

#ifdef TODO
  add(AUDIO_PREFERENCES, makeCallback(cc,
                                      &ComponentContainer::audioPreferences),
      "Audio Preferences...", "File",
      "Open the Audio Preferences pane.", ';');

  add(CLEAR_TIME, makeCallback(&instal, &MainPage::clearTime),
      "Clear Time Stretch", "Loop",
      "Clear all time and pitch shifting");
  add(TREE_CLEAR, makeCallback(cc, &ComponentContainer::clearTree),
      "Clear Workspace", "Loop",
      "Remove all files and directories from the workspace area.");
  // add(FILE_CLEAR, make, &ComponentContainer::clearFile);
#endif

  registerAllCommandsForTarget();
}

