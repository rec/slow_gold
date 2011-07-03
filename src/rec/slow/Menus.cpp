#include "rec/slow/Menus.h"
#include "rec/base/ArraySize.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Target.h"
#include "rec/util/Cuttable.h"

namespace rec {
namespace slow {

Menus::Menus(Instance* i) : HasInstance(i) {}

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Audio", "Transport", "Loops",
                                "Select"};
  return StringArray(NAMES, arraysize(NAMES));
}

void Menus::add(PopupMenu* menu, Command command, bool enable) {
  target()->addCommandItem(menu, command, enable);
}

static void addTenSubitems(Menus* menus, PopupMenu* menu,
                           Command command, const String& name) {
  PopupMenu sub;
  for (int i = 0; i < 10; ++i)
    menus->add(&sub, static_cast<Command>(command + i));
  menu->addSubMenu(name, sub);
}

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  using command::Command;
  PopupMenu m;
  if (menuName == "File") {
    add(&m, Command::OPEN);
    add(&m, Command::CLOSE_FILE);
    add(&m, Command::EJECT_CDS);

    m.addSeparator();

    // add(&m, Command::CLEAR_NAVIGATOR);
    add(&m, Command::KEYBOARD_MAPPINGS);
    add(&m, Command::MIDI_MAPPINGS);

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
    add(&m, Command::CUT, canCut());
    add(&m, Command::COPY, canCopy());
    add(&m, Command::PASTE, canPaste());

  } else if (menuName == "Audio") {
    add(&m, Command::MUTE_VOLUME_TOGGLE);
    add(&m, Command::DIM_VOLUME_TOGGLE);
    add(&m, Command::NUDGE_VOLUME_UP);
    add(&m, Command::NUDGE_VOLUME_DOWN);
    add(&m, Command::RESET_GAIN_TO_UNITY);

    m.addSeparator();
    add(&m, Command::AUDIO_PREFERENCES);

  } else if (menuName == "Select") {
    add(&m, Command::SELECT_ALL);
    add(&m, Command::DESELECT_ALL);
    add(&m, Command::INVERT_LOOP_SELECTION);

    PopupMenu selMenu;
    addTenSubitems(this, &m, Command::SELECT_0, "Select...");
    addTenSubitems(this, &m, Command::SELECT_ONLY_0, "Select Only...");
    addTenSubitems(this, &m, Command::TOGGLE_0, "Toggle...");
    addTenSubitems(this, &m, Command::UNSELECT_0, "Unselect...");
    // m.addSubMenu("Select", selMenu);

  } else if (menuName == "Transport") {
    add(&m, Command::JUMP_TO_0);
    add(&m, Command::JUMP_TO_PREVIOUS_SEGMENT);
    add(&m, Command::JUMP_TO_NEXT_SEGMENT);
    add(&m, Command::JUMP_TO_LAST_SEGMENT);

    addTenSubitems(this, &m, Command::JUMP_TO_0, "Jump to...");

  } else if (menuName == "Loops") {
    add(&m, Command::CLEAR_LOOPS);
    add(&m, Command::ADD_LOOP_POINT);
  }

  return m;
}

}  // namespace slow
}  // namespace rec

