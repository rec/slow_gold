#include "rec/slow/Menus.h"
#include "rec/base/ArraySize.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Position.h"
#include "rec/slow/Target.h"
#include "rec/util/Cuttable.h"

using namespace rec::command;

namespace rec {
namespace slow {

Menus::Menus(Instance* i) : HasInstance(i) {}

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Audio", "Transport", "Select"};
  return StringArray(NAMES, arraysize(NAMES));
}

void Menus::add(PopupMenu* menu, Command::Type command, bool enable,
                const String& name) {
  target()->targetManager()->addCommandItem(menu, command, enable, name);
}

static void addBank(Menus* menus, PopupMenu* menu,
                    Command::Type command, const String& name) {
  PopupMenu sub;
  for (int i = 0; i <= LAST - FIRST; ++i)
    menus->add(&sub, static_cast<Command::Type>(command + i));

  sub.addSeparator();

  for (int i = 0; i != SLOT_COUNT; ++i)
    menus->add(&sub, static_cast<Command::Type>(command + LAST - FIRST + i + 1));

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
    add(&m, Command::QUIT);
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
    add(&m, Command::TOGGLE_WHOLE_SONG_LOOP);

    m.addSeparator();

    addBank(this, &m, Command::SELECT, "Select...");
    addBank(this, &m, Command::SELECT_ONLY, "Select Only...");
    addBank(this, &m, Command::TOGGLE, "Toggle...");
    addBank(this, &m, Command::UNSELECT, "Unselect...");

  } else if (menuName == "Transport") {
    add(&m, Command::TOGGLE_START_STOP);
    add(&m, Command::ADD_LOOP_POINT);
    add(&m, Command::CLEAR_LOOPS);

    m.addSeparator();

    addBank(this, &m, Command::JUMP, "Jump To...");
    addBank(this, &m, Command::JUMP_SELECTED, "Jump To Selected...");
  }

  return m;
}

}  // namespace slow
}  // namespace rec

