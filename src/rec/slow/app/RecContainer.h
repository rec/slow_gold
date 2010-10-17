#ifndef __REC_REC_CONTAINER
#define __REC_REC_CONTAINER

#include <algorithm>

#include "rec/gui/RecentFiles.h"
#include "rec/slow/app/ComponentContainer.h"
#include "rec/slow/app/MainPageComponent.h"

namespace rec {

class RecContainer : public ComponentContainer {
 public:
  RecContainer() : mainPage_(new MainPageComponent) {
    show(mainPage_);
  }

  virtual const StringArray getMenuBarNames() {
    static const char* const names[] = {"File", "Edit", NULL};
    return StringArray(names);
  }

  static const int NEW_WINDOW_MENU_INDEX = 1001;

  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& menuName) {
    PopupMenu menu;
    if (menuName == "File") {
      menu.addItem(NEW_WINDOW_MENU_INDEX, "New window");
      gui::RecentFiles recent = gui::getSortedRecentFiles();
      PopupMenu submenu;
      for (int i = 0; i < recent.file_size(); ++i)
        submenu.addItem(i + 1, recent.file(i).name().c_str());

      menu.addSubMenu("Open recent", submenu);
    } else if (menuName == "Edit") {
      menu.addItem(1, "Cut");
      menu.addItem(2, "Paste");
    }

    return menu;
  }

  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {
    if (topLevelMenuIndex == 0) {
      if (menuItemID == NEW_WINDOW_MENU_INDEX) {
      } else {
        mainPage_->loadRecentFile(menuItemID);
      }
    } else if (topLevelMenuIndex == 1) {
      if (menuItemID == 1)
        mainPage_->cut();
      else if (menuItemID == 2)
        mainPage_->paste();
    }
  }
  juce_UseDebuggingNewOperator
 private:
  MainPageComponent* mainPage_;


};

}

#endif  // __REC_REC_CONTAINER
