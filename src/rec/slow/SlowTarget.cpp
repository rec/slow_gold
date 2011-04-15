#include "rec/gui/Dialog.h"
#include "rec/slow/SlowTarget.h"

namespace rec {
namespace slow {

SlowTarget::SlowTarget(Instance* i, MainPage* mp, ComponentContainer* cc) {
  using rec::command::Command;
  using thread::makeCallback;

  add(COPY, makeCallback(&copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.");

  add(CUT, makeCallback(&cutToClipboard),
      "Cut", "Edit"
      "Copy the current selection to the clipboard and clear the selection.");

  add(EJECT, makeCallback(&cd::ejectAll),
      "Eject All", "Disk",
      "Eject all CDs and DVDs");

  add(PASTE, makeCallback(&pasteFromClipboard),
      "Paste", "Edit"
      "Replace the current selection with a copy of the clipboard.");

  add(QUIT, makeCallback(JUCEApplication::getInstance(),
                         &JUCEApplication::systemRequestedQuit),
      "Quit", "File",
      "Quit SlowGold");

  add(OPEN, makeCallback(&gui::dialog::openVirtualFile,
                         persist::data<VirtualFile>()),
      "Open...", "File",
      "Open dialog to select a new audio file for looping.");

  add(CLEAR_LOOPS, makeCallback(mp, &MainPage::clearLoops),
      "Clear Loops", "Loop",
      "Get rid of all loop points");

  add(CLEAR_SELECTION, makeCallback(mp, &MainPage::clearSelection),
      "Clear Selection", "Loop",
      "Unselect all the loop points");
  add(CLEAR_TIME, makeCallback(mp, &MainPage::clearTime),
      "Clear Time Stretch", "Loop",
      "Clear all time and pitch shifting");
  add(CLOSE, makeCallback(&persist::data<VirtualFile>(), VirtualFile()),
      "Close", "File",
      "Close the current file");

  Add(TREE_CLEAR, makeCallback(cc, &ComponentContainer::clearTree),
      "Clear Workspace", "Workspace",
      "Remove all files and directories from the workspace area.");
  // add(FILE_CLEAR, make, &ComponentContainer::clearFile);
  add(AUDIO_PREFERENCES, makeCallback(cc,
                                      &ComponentContainer::audioPreferences),
      "Audio Preferences...", "Audio",
      "Open the Audio Preferences pane.");
}

}  // namespace slow
}  // namespace rec
