#include "rec/slow/app/ComponentContainer.h"

#include "rec/gui/RecentFiles.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/slow/app/MainPageComponent.h"
#include "rec/slow/app/AudioSetupPage.h"
#include "rec/util/thread/MakeThread.h"

namespace rec {
namespace slow {

ComponentContainer::ComponentContainer(MainPageComponent* c) : mainComponent_(c) {
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
    menu.addItem(CUT, "Cut");
    menu.addItem(PASTE, "Paste");
    menu.addItem(CLEAR_FILE, "Clear file");
    menu.addItem(CLEAR_TIME, "Clear time and pitch shift to 1");
    menu.addItem(CLEAR_TREE, "Clear directory window");
    menu.addItem(AUDIO_PREFERENCES, "Set audio preferences...");
  }

  return menu;
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

void ComponentContainer::menuItemSelected(int menuItemID, int topLevelMenuIndex) {
  thread::runInNewThread("doMenuSelected", 5,
                         this, &ComponentContainer::doMenuItemSelected,
                         menuItemID, topLevelMenuIndex);
}

void ComponentContainer::clearTree() {
  persist::data<file::VirtualFileList>()->clear();
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

void ComponentContainer::doMenuItemSelected(int itemID, int topLevelMenuIndex) {
  MainPage* mainPage = mainComponent_->mainPage();
  switch (itemID) {
    case OPEN:   mainPage->doOpen(); break;
    case CLOSE:  mainPage->doClose(); break;
    case CUT:    mainComponent_->cut(); break;
    case PASTE:  mainComponent_->paste(); break;
    case EJECT:  eject(); break;
    case QUIT:   quit(); break;
    case CLEAR_TREE: clearTree(); break;
    case CLEAR_TIME: mainPage->clearTime(); break;
    case CLEAR_FILE: clearFile(); break;
    case AUDIO_PREFERENCES: thread::callAsync(this, &ComponentContainer::audioPreferences); break;
    default:     mainComponent_->loadRecentFile(itemID - RECENT_FILES); break;
  }
}

ApplicationCommandTarget* ComponentContainer::getNextCommandTarget() {
  return findFirstTargetParentComponent();
}

}  // namespace slow
}  // namespace rec
