#ifndef __REC_REC_CONTAINER
#define __REC_REC_CONTAINER

#include <algorithm>

#include "rec/slow/RecentFiles.h"
#include "rec/app/ComponentContainer.h"
#include "rec/components/MainPageComponent.h"

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

  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& menuName) {
    PopupMenu menu;
    if (menuName == "File") {
      slow::RecentFiles recent = slow::getSortedRecentFiles();
      PopupMenu submenu;
      for (int i = 0; i < recent.file_size(); ++i)
        submenu.addItem(i + 1, recent.file(i).name().c_str());

      menu.addSubMenu("Open recent", submenu);
    }
    return menu;
  }

  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {
    mainPage_->loadRecentFile(menuItemID);
  }

 private:
  MainPageComponent* mainPage_;

  juce_UseDebuggingNewOperator
};

}

#endif  // __REC_REC_CONTAINER
