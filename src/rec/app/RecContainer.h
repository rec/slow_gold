#ifndef __REC_REC_CONTAINER
#define __REC_REC_CONTAINER

#include "rec/app/ComponentContainer.h"
#include "rec/components/MainPageComponent.h"
#include "rec/slow/Preferences.h"

namespace rec {

class RecContainer : public ComponentContainer<RecWindow> {
 public:
  RecContainer(RecWindow* window)
      : ComponentContainer<RecWindow>(window),
        mainPage_(new MainPageComponent) {
    show(mainPage_);
  }

  virtual const StringArray getMenuBarNames() {
    static const char* const names[] = {"File", "Edit", NULL};
    return StringArray(names);
  }

  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& menuName) {
    PopupMenu menu;
    if (menuName == "File") {
      slow::proto::Preferences prefs(rec::slow::getPreferences());
      if (prefs.has_recent_files()) {
        const slow::RecentFiles& recent = prefs.recent_files();
        PopupMenu submenu;
        int size = recent.name_size();
        for (int i = size; i > 0; --i)
          submenu.addItem(i, rec::persist::copy(recent.name(i - 1)));

        menu.addSubMenu("Open recent", submenu);
      }
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
