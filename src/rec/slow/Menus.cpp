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

Menus::Menus(Instance* i) : HasInstance(i) {}

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Audio", "Transport", "Select"};
  return StringArray(NAMES, arraysize(NAMES));
}

void Menus::addCommandItem(PopupMenu* menu, CommandID command, bool enable,
                           const String& name) {
  if (ApplicationCommandInfo* info = target()->targetManager()->getInfo(command)) {
    if (name.length())
      info->shortName = name;
    DCHECK(info->shortName.length()) << "No name for command "
                                     << slow::Position::commandIDName(command);
    info->setActive(enable);
    menu->addCommandItem(target()->targetManager()->commandManager(), command, name);
  } else {
    LOG(ERROR) << "Can't add item " << Position::commandIDName(command);
  }
}

namespace {

void addBank(Menus* menus, PopupMenu* menu, Command::Type command,
             const String& name) {
  PopupMenu sub;
  for (int i = Position::FIRST; i < SLOT_COUNT; ++i) {
    if (i == 0)
      sub.addSeparator();

    menus->addCommandItem(&sub, Position::toCommandID(i, command));
  }

  menu->addSubMenu(name, sub);
}

void addFileMenu(Menus* m, PopupMenu* popup) {
  m->addCommandItem(popup, Command::OPEN);
  m->addCommandItem(popup, Command::CLOSE_FILE);
  m->addCommandItem(popup, Command::EJECT_CDS);

  popup->addSeparator();

  // m->addCommandItem(popup, Command::CLEAR_NAVIGATOR);
  m->addCommandItem(popup, Command::KEYBOARD_MAPPINGS);
  m->addCommandItem(popup, Command::MIDI_MAPPINGS);

  std::vector<string> recent = rec::gui::getRecentFileNames();
  PopupMenu submenu;
  for (int i = 0; i < recent.size(); ++i) {
    CommandID id = Position::toCommandID(i, Command::RECENT_FILES);
    m->addCommandItem(&submenu, id, true, str(recent[i]));
  }

  popup->addSubMenu("Open recent", submenu);

#if !JUCE_MAC
    m->addCommandItem(&m, Command::QUIT);
#endif
}

}  // namespace


const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  using command::Command;

  PopupMenu m;
  if (menuName == "File") {
    addFileMenu(this, &m);

  } else if (menuName == "Edit") {
    addCommandItem(&m, Command::UNDO, canUndo());
    addCommandItem(&m, Command::REDO, canRedo());

    m.addSeparator();

    addCommandItem(&m, Command::CUT, canCut());
    addCommandItem(&m, Command::COPY, canCopy());
    addCommandItem(&m, Command::PASTE, canPaste());

  } else if (menuName == "Audio") {
    addCommandItem(&m, Command::MUTE_VOLUME_TOGGLE);
    addCommandItem(&m, Command::DIM_VOLUME_TOGGLE);
    addCommandItem(&m, Command::NUDGE_VOLUME_UP);
    addCommandItem(&m, Command::NUDGE_VOLUME_DOWN);
    addCommandItem(&m, Command::RESET_GAIN_TO_UNITY);

    m.addSeparator();

    addCommandItem(&m, Command::AUDIO_PREFERENCES);

  } else if (menuName == "Select") {
    addCommandItem(&m, Command::SELECT_ALL);
    addCommandItem(&m, Command::DESELECT_ALL);
    addCommandItem(&m, Command::INVERT_LOOP_SELECTION);
    addCommandItem(&m, Command::TOGGLE_WHOLE_SONG_LOOP);

    m.addSeparator();

    addBank(this, &m, Command::SELECT, "Select...");
    addBank(this, &m, Command::SELECT_ONLY, "Select Only...");
    addBank(this, &m, Command::TOGGLE, "Toggle...");
    addBank(this, &m, Command::UNSELECT, "Unselect...");

  } else if (menuName == "Transport") {
    addCommandItem(&m, Command::TOGGLE_START_STOP);
    addCommandItem(&m, Command::ADD_LOOP_POINT);
    addCommandItem(&m, Command::CLEAR_LOOPS);

    m.addSeparator();

    addBank(this, &m, Command::JUMP, "Jump To...");
    addBank(this, &m, Command::JUMP_SELECTED, "Jump To Selected...");
  }

  return m;
}

}  // namespace slow
}  // namespace rec

