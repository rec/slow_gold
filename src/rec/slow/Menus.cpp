#include "rec/slow/Menus.h"
#include "rec/base/ArraySize.h"
#include "rec/command/Command.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Target.h"
#include "rec/util/Cuttable.h"

namespace rec {
namespace slow {

Menus::Menus(Instance* i) : HasInstance(i) {}

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Loop"};
  return StringArray(NAMES, arraysize(NAMES));
}

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  using command::Command;
  PopupMenu m;
  if (menuName == "File") {
    target()->addCommandItem(&m, Command::OPEN);
    target()->addCommandItem(&m, Command::CLOSE_FILE);
    target()->addCommandItem(&m, Command::EJECT_CDS);
    target()->addCommandItem(&m, Command::CLEAR_NAVIGATOR);
    target()->addCommandItem(&m, Command::AUDIO_PREFERENCES);
    target()->addCommandItem(&m, Command::KEYBOARD_MAPPINGS);

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
    target()->addCommandItem(&m, QUIT);
#endif

  } else if (menuName == "Edit") {
    target()->addCommandItem(&m, Command::CUT, canCut());
    target()->addCommandItem(&m, Command::COPY, canCopy());
    target()->addCommandItem(&m, Command::PASTE, canPaste());

  } else if (menuName == "Loop") {
    // target()->addCommandItem(&m, Command::CLEAR_SELECTION);
    target()->addCommandItem(&m, Command::CLEAR_LOOPS);
    target()->addCommandItem(&m, Command::SELECT_ALL);
    target()->addCommandItem(&m, Command::DESELECT_ALL);
    target()->addCommandItem(&m, Command::ADD_LOOP_POINT);
    target()->addCommandItem(&m, Command::CLEAR_SELECTION);
    target()->addCommandItem(&m, Command::CONTRACT_FROM_NEXT_LOOP_POINT);
    target()->addCommandItem(&m, Command::CONTRACT_FROM_PREVIOUS_LOOP_POINT);
    target()->addCommandItem(&m, Command::INVERT_LOOP_SELECTION);
    target()->addCommandItem(&m, Command::EXTEND_TO_NEXT_LOOP_POINT);
    target()->addCommandItem(&m, Command::EXTEND_TO_PREVIOUS_LOOP_POINT);
    target()->addCommandItem(&m, Command::JUMP_TO_NEXT_LOOP_POINT);
    target()->addCommandItem(&m, Command::JUMP_TO_PREVIOUS_LOOP_POINT);
    target()->addCommandItem(&m, Command::JUMP_TO_START);
  }

  return m;
}

}  // namespace slow
}  // namespace rec

