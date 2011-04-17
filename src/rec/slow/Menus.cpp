#include "rec/slow/Menus.h"
#include "rec/base/ArraySize.h"

namespace rec {
namespace slow {

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Loop"};
  return StringArray(NAMES, arraysize(NAMES));
}

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& name) {
  using rec::command::Command;

  PopupMenu m;
  if (menuName == "File") {
    add(&m, OPEN);
    add(&m, CLOSE);
    add(&m, EJECT);
    add(&m, AUDIO_PREFERENCES);
    add(&m, TREE_CLEAR);

#ifdef RECENT_FILES_ENABLED
    gui::RecentFiles recent = gui::getSortedRecentFiles();
    PopupMenu submenu;
    for (int i = 0; i < recent.file_size(); ++i)
      submenu.addCommandItem(RECENT_FILES_OFFSET + i, getFilename(recent.file(i).file()));

    menu.addSubMenu("Open recent", submenu);
#endif

#if !JUCE_MAC
    add(&m, QUIT);
#endif

  } else if (menuName == "Edit") {
    add(&m, CUT);
    add(&m, COPY);
    add(&m, PASTE);

  } else if (menuName == "Loop") {
    add(&m, CLEAR_SELECTION);
    add(&m, CLEAR_LOOPS);
    add(&m, CLEAR_TIME);
  }


  return menu;
}

}  // namespace slow
}  // namespace rec

