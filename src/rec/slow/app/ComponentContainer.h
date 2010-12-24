#ifndef __REC_COMPONENT_CONTAINER
#define __REC_COMPONENT_CONTAINER

#include "rec/base/base.h"
#include "rec/gui/RecentFiles.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/slow/app/MainPageComponent.h"

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

  virtual const PopupMenu getMenuForIndex(int menuIndex, const String& menuName) {
    PopupMenu menu;
    if (menuName == "File") {
      menu.addItem(999, "Open...");

      gui::RecentFiles recent = gui::getSortedRecentFiles();
      PopupMenu submenu;
      for (int i = 0; i < recent.file_size(); ++i)
        submenu.addItem(i + 1, getFilename(recent.file(i).file()));

      menu.addSubMenu("Open recent", submenu);
    } else if (menuName == "Edit") {
      menu.addItem(1, "Cut");
      menu.addItem(2, "Paste");
    }

    return menu;
  }

  virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) {
    if (topLevelMenuIndex == 0) {
      if (menuItemID != 999)
        mainPage_->loadRecentFile(menuItemID);
    } else if (topLevelMenuIndex == 1) {
      if (menuItemID == 1)
        mainPage_->cut();
      else if (menuItemID == 2)
        mainPage_->paste();
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
