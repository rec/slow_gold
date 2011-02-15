#include "rec/slow/ComponentContainer.h"

#include "rec/gui/RecentFiles.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/slow/MainPageComponent.h"
#include "rec/slow/AudioSetupPage.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/Cuttable.h"

using namespace rec::gui;

namespace rec {
namespace slow {

namespace {

typedef void (ComponentContainer::*ComponentCommand)();

ComponentCommand commands[ComponentContainer::LAST_MENU_ITEM] = {
  NULL,
  &ComponentContainer::open,
  &ComponentContainer::close,
  &ComponentContainer::cut,
  &ComponentContainer::copy,
  &ComponentContainer::paste,
  &ComponentContainer::quit,
  &ComponentContainer::eject,
  &ComponentContainer::clearTree,
  &ComponentContainer::clearTime,
  &ComponentContainer::clearFile,
  &ComponentContainer::audioPreferences,
  &ComponentContainer::clearSelection,
  &ComponentContainer::clearLoops,
};

}

void ComponentContainer::open() {
   mainComponent_->mainPage()->doOpen();
}

void ComponentContainer::close() {
  mainComponent_->mainPage()->doClose();
}

void ComponentContainer::cut() {
  cutToClipboard();
}

void ComponentContainer::copy() {
  copyToClipboard();
}

void ComponentContainer::paste() {
  pasteFromClipboard();
}

void ComponentContainer::quit() {
  JUCEApplication::getInstance()->systemRequestedQuit();
}

void ComponentContainer::eject() {
  StringArray burners = AudioCDBurner::findAvailableDevices();
  for (int i = 0; i < burners.size(); ++i) {
    ptr<AudioCDBurner>(AudioCDBurner::openDevice(i))->openTray();
    DLOG(INFO) << "Burner " << burners[i].toCString();
  }
}

void ComponentContainer::clearTree() {
  persist::data<file::VirtualFileList>()->clear();
}

void ComponentContainer::clearTime() {
  mainComponent_->mainPage()->clearTime();
}

void ComponentContainer::clearFile() {
  persist::data<file::VirtualFile>()->clear();
}

void ComponentContainer::audioPreferences() {
  juce::DialogWindow::showModalDialog("Set Audio Preferences",
                                      mainComponent_->audioSetupPage(),
                                      mainComponent_.get(),
                                      Colours::white, true);
}

void ComponentContainer::clearSelection() {
  mainComponent_->mainPage()->clearSelection();
}

void ComponentContainer::clearLoops() {
  mainComponent_->mainPage()->clearLoops();
}

ComponentContainer::ComponentContainer(MainPageComponent* c) :
    Component("ComponentContainer"),
    mainComponent_(c) {
  addAndMakeVisible(c);
}

ComponentContainer::~ComponentContainer() {}

void ComponentContainer::resized() {
  mainComponent_->setBounds(0, 0, getWidth(), getHeight());
}

const StringArray ComponentContainer::getMenuBarNames() {
  static const char* const names[] = {"File", "Edit", NULL};
  return StringArray(names);
}

const PopupMenu ComponentContainer::getMenuForIndex(int menuIndex,
                                                    const String& menuName) {
  PopupMenu menu;
  if (menuName == "File") {
    menu.addItem(OPEN, "Open...");
    menu.addItem(CLOSE, "Close");

    gui::RecentFiles recent = gui::getSortedRecentFiles();
    PopupMenu submenu;
    for (int i = 0; i < recent.file_size(); ++i)
      submenu.addItem(RECENT_FILES + i, getFilename(recent.file(i).file()));

    menu.addSubMenu("Open recent", submenu);
    menu.addItem(EJECT, "Eject all discs");
    menu.addItem(QUIT, "Quit");

  } else if (menuName == "Edit") {
    menu.addItem(CUT, "Cut", canCutOrCopy());
    menu.addItem(COPY, "Copy", canCutOrCopy());
    menu.addItem(PASTE, "Paste", canPaste());
    menu.addItem(CLEAR_FILE, "Clear file");
    menu.addItem(CLEAR_SELECTION, "Clear selection of loop points");
    menu.addItem(CLEAR_LOOPS, "Clear loops");
    menu.addItem(CLEAR_TIME, "Clear time and pitch shift to 1");
    menu.addItem(CLEAR_TREE, "Clear bookmarks area");
    menu.addItem(AUDIO_PREFERENCES, "Set audio preferences...");
  }

  return menu;
}

void ComponentContainer::menuItemSelected(int menuItemID, int menuIndex) {
  thread::runInNewThread("ComponentContainer::doMenuSelected", 5,
                         this, &ComponentContainer::doMenuItemSelected,
                         menuItemID, menuIndex);
}

void ComponentContainer::doMenuItemSelected(int itemID, int topLevelMenuIndex) {
  if (itemID < RECENT_FILES)
    (this->*(commands[itemID]))();
  else
    mainComponent_->loadRecentFile(itemID - RECENT_FILES);
}

ApplicationCommandTarget* ComponentContainer::getNextCommandTarget() {
  return findFirstTargetParentComponent();
}

}  // namespace slow
}  // namespace rec
