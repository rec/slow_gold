#include "rec/gui/Dialog.h"
#include "rec/slow/Target.h"

namespace rec {
namespace slow {

Target::Target(Instance* i, MainPage* mp, ComponentContainer* cc) {
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

  add(CLEAR_LOOPS, makeCallback(mp, &MainPage::clearLoops),
      "Clear Loops", "Loop",
      "Get rid of all loop points");

  add(CLEAR_SELECTION, makeCallback(mp, &MaoverinPage::clearSelection),
      "Clear Selection", "Loop",
      "Unselect all the loop points");
  add(CLEAR_TIME, makeCallback(mp, &MainPage::clearTime),
      "Clear Time Stretch", "Loop",
      "Clear all time and pitch shifting");
  add(CLOSE, makeCallback(&persist::data<VirtualFile>(), VirtualFile()),
      "Close", "File",
      "Close the current file", 'w');

  Add(TREE_CLEAR, makeCallback(cc, &ComponentContainer::clearTree),
      "Clear Workspace", "Loop",
      "Remove all files and directories from the workspace area.");
  // add(FILE_CLEAR, make, &ComponentContainer::clearFile);
  add(AUDIO_PREFERENCES, makeCallback(cc,
                                      &ComponentContainer::audioPreferences),
      "Audio Preferences...", "File",
      "Open the Audio Preferences pane.", ';');
}

