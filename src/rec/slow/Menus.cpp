#include "rec/slow/Menus.h"
#include "rec/base/ArraySize.h"
#include "rec/gui/RecentFiles.h"
#include "rec/util/Undo.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Position.h"
#include "rec/slow/Target.h"
#include "rec/util/Cuttable.h"

using namespace rec::command;

namespace rec {
namespace slow {

static const int SLOT_COUNT = 10;

// TODO: only place "10" items is hard-coded into the code - remove!

Menus::Menus(Instance* i) : HasInstance(i) {}

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Audio", "Transport", "Select"};
  return StringArray(NAMES, arraysize(NAMES));
}

void Menus::addCommand(PopupMenu* menu, CommandID command, bool enable,
                       const String& name) {
  target()->targetManager()->addCommandItem(menu, command, enable, name);
}

static void addBank(Menus* menus, PopupMenu* menu,
                    Command::Type command, const String& name) {
  PopupMenu sub;
  for (int i = Position::FIRST; i < SLOT_COUNT; ++i) {
    if (i == 0)
      sub.addSeparator();

    menus->addCommand(&sub, Position::toCommandID(i, command));
  }

  menu->addSubMenu(name, sub);
}

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  using command::Command;
  PopupMenu m;
  if (menuName == "File") {
    addCommand(&m, Command::OPEN);
    addCommand(&m, Command::CLOSE_FILE);
    addCommand(&m, Command::EJECT_CDS);

    m.addSeparator();

    // addCommand(&m, Command::CLEAR_NAVIGATOR);
    addCommand(&m, Command::KEYBOARD_MAPPINGS);
    addCommand(&m, Command::MIDI_MAPPINGS);

#ifndef RECENT_FILES_ENABLED
    std::vector<string> recent = rec::gui::getRecentFileNames();
    PopupMenu submenu;
    for (int i = 0; i < recent.size(); ++i) {
      CommandID id = Position::toCommandID(i, Command::RECENT_FILES);
      addCommand(&submenu, id, true, str(recent[i]));
    }

    m.addSubMenu("Open recent", submenu);
#endif

#if !JUCE_MAC
    addCommand(&m, Command::QUIT);
#endif

  } else if (menuName == "Edit") {
    addCommand(&m, Command::UNDO, canUndo());
    addCommand(&m, Command::REDO, canRedo());

    m.addSeparator();

    addCommand(&m, Command::CUT, canCut());
    addCommand(&m, Command::COPY, canCopy());
    addCommand(&m, Command::PASTE, canPaste());

  } else if (menuName == "Audio") {
    addCommand(&m, Command::MUTE_VOLUME_TOGGLE);
    addCommand(&m, Command::DIM_VOLUME_TOGGLE);
    addCommand(&m, Command::NUDGE_VOLUME_UP);
    addCommand(&m, Command::NUDGE_VOLUME_DOWN);
    addCommand(&m, Command::RESET_GAIN_TO_UNITY);

    m.addSeparator();

    addCommand(&m, Command::AUDIO_PREFERENCES);

  } else if (menuName == "Select") {
    addCommand(&m, Command::SELECT_ALL);
    addCommand(&m, Command::DESELECT_ALL);
    addCommand(&m, Command::INVERT_LOOP_SELECTION);
    addCommand(&m, Command::TOGGLE_WHOLE_SONG_LOOP);

    m.addSeparator();

    addBank(this, &m, Command::SELECT, "Select...");
    addBank(this, &m, Command::SELECT_ONLY, "Select Only...");
    addBank(this, &m, Command::TOGGLE, "Toggle...");
    addBank(this, &m, Command::UNSELECT, "Unselect...");

  } else if (menuName == "Transport") {
    addCommand(&m, Command::TOGGLE_START_STOP);
    addCommand(&m, Command::ADD_LOOP_POINT);
    addCommand(&m, Command::CLEAR_LOOPS);

    m.addSeparator();

    addBank(this, &m, Command::JUMP, "Jump To...");
    addBank(this, &m, Command::JUMP_SELECTED, "Jump To Selected...");
  }

  return m;
}

}  // namespace slow
}  // namespace rec

