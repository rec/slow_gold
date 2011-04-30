#include "rec/slow/Menus.h"
#include "rec/base/ArraySize.h"
#include "rec/command/Command.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Target.h"

namespace rec {
namespace slow {

Menus::Menus(Instance* i) : HasInstance(i) {
  // i->target_.setApplicationCommandManagerToWatch(this); // TODO
}

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Loop"};
  return StringArray(NAMES, arraysize(NAMES));
}

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  typedef command::Command Command;

  PopupMenu m;
  if (menuName == "File") {
    add(&m, Command::OPEN);
    add(&m, Command::CLOSE);
    add(&m, Command::EJECT);
    add(&m, Command::AUDIO_PREFERENCES);
    add(&m, Command::CLEAR_TREE);

#ifdef RECENT_FILES_ENABLED
    gui::RecentFiles recent = gui::getSortedRecentFiles();
    PopupMenu submenu;
    for (int i = 0; i < recent.file_size(); ++i) {
      submenu.addCommandItem(Command::RECENT_FILES_OFFSET + i,
                             getFilename(recent.file(i).file()));
    }

    menu.addSubMenu("Open recent", submenu);
#endif

#if !JUCE_MAC
    add(&m, QUIT);
#endif

  } else if (menuName == "Edit") {
    add(&m, Command::CUT);
    add(&m, Command::COPY);
    add(&m, Command::PASTE);

  } else if (menuName == "Loop") {
    add(&m, Command::CLEAR_SELECTION);
    add(&m, Command::CLEAR_LOOPS);
    add(&m, Command::CLEAR_TIME);
  }

  return m;
}

void Menus::add(PopupMenu* m, CommandID c) {
  target()->addCommandItem(m, c);
}

}  // namespace slow
}  // namespace rec

