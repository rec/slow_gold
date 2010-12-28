#ifndef __REC_COMPONENT_CONTAINER
#define __REC_COMPONENT_CONTAINER

#include "rec/base/base.h"
#include "rec/gui/RecentFiles.h"
#include "rec/util/file/VolumeFile.h"
#include "rec/slow/app/MainPageComponent.h"
#include "rec/util/thread/MakeThread.h"

using namespace juce;

namespace rec {
namespace slow {

class ComponentContainer : public Component,
                           public MenuBarModel,
                           public ApplicationCommandTarget {
 public:
  ComponentContainer(MainPageComponent* c) : mainPage_(c) { addAndMakeVisible(c); }

  virtual ~ComponentContainer() {}

  virtual void resized() {
    mainPage_->setBounds(0, 0, getWidth(), getHeight());
  }

  virtual const StringArray getMenuBarNames() {
    static const char* const names[] = {"File", "Edit", NULL};
    return StringArray(names);
  }

  enum MenuItems {
    OPEN = 1,
    CLOSE,
    CUT,
    PASTE,
    QUIT,
    EJECT,
    RECENT_FILES
  };

  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& menuName) {
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
    }

    return menu;
  }

  void quit() {
    JUCEApplication::getInstance()->systemRequestedQuit();
  }

  void eject() {
    StringArray burners = AudioCDBurner::findAvailableDevices();
    for (int i = 0; i < burners.size(); ++i)
      ptr<AudioCDBurner>(AudioCDBurner::openDevice(i))->openTray();
  }

  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {
    thread::runInNewThread("doMenuSelected", 5, 
    											 this, &ComponentContainer::doMenuItemSelected,
                           menuItemID, topLevelMenuIndex);
  }

  void doMenuItemSelected(int menuItemID, int topLevelMenuIndex) {
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
      default:     mainPage_->loadRecentFile(menuItemID - RECENT_FILES); break;
    }
  }

  // ApplicationCommandTarget virtual methods.
  virtual void getAllCommands(Array <CommandID>& commands) {}
  virtual void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) {}
  virtual bool perform(const InvocationInfo& info) { return false; }

  virtual ApplicationCommandTarget* getNextCommandTarget() {
    return findFirstTargetParentComponent();
  }

 protected:
  ptr<MainPageComponent> mainPage_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMPONENT_CONTAINER
