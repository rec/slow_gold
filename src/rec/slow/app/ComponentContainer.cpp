#include "rec/slow/app/ComponentContainer.h"

#include "rec/gui/RecentFiles.h"
#include "rec/util/file/VolumeFile.h"
#include "rec/slow/app/MainPageComponent.h"
#include "rec/util/thread/MakeThread.h"

namespace rec {
namespace slow {

ComponentContainer::ComponentContainer(MainPageComponent* c) : mainPage_(c) {
  addAndMakeVisible(c);
}

ComponentContainer::~ComponentContainer() {}

void ComponentContainer::resized() {
  mainPage_->setBounds(0, 0, getWidth(), getHeight());
}

const StringArray ComponentContainer::getMenuBarNames() {
  static const char* const names[] = {"File", "Edit", NULL};
  return StringArray(names);
}

const PopupMenu ComponentContainer::getMenuForIndex(int menuIndex, const String& menuName) {
  DLOG(INFO) << "getMenuForIndex";
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
    menu.addItem(CLEAR_TREE, "Clear directory window");
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
  persist::data<file::VolumeFileList>()->clear();
}

void ComponentContainer::doMenuItemSelected(int menuItemID, int topLevelMenuIndex) {
  DLOG(INFO) << "menuItemSelected: "
             << menuItemID << ", " << topLevelMenuIndex;
  MainPage* mainPage = mainPage_->mainPage();
  switch (menuItemID) {
    case OPEN:   mainPage->doOpen(); break;
    case CLOSE:  mainPage->doClose(); break;
    case CUT:    mainPage_->cut(); break;
    case PASTE:  mainPage_->paste(); break;
    case EJECT:  eject(); break;
    case QUIT:   quit(); break;
    case CLEAR_TREE: clearTree(); break;
    default:     mainPage_->loadRecentFile(menuItemID - RECENT_FILES); break;
  }
}

ApplicationCommandTarget* ComponentContainer::getNextCommandTarget() {
  return findFirstTargetParentComponent();
}

}  // namespace slow
}  // namespace rec
