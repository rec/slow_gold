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

void addEditMenu(Menus* m, PopupMenu* popup) {
  m->addCommandItem(popup, Command::UNDO, canUndo());
  m->addCommandItem(popup, Command::REDO, canRedo());

  popup->addSeparator();

  m->addCommandItem(popup, Command::CUT, canCut());
  m->addCommandItem(popup, Command::COPY, canCopy());
  m->addCommandItem(popup, Command::PASTE, canPaste());
}

void addAudioMenu(Menus* m, PopupMenu* popup) {
  m->addCommandItem(popup, Command::MUTE_VOLUME_TOGGLE);
  m->addCommandItem(popup, Command::DIM_VOLUME_TOGGLE);
  m->addCommandItem(popup, Command::NUDGE_VOLUME_UP);
  m->addCommandItem(popup, Command::NUDGE_VOLUME_DOWN);
  m->addCommandItem(popup, Command::RESET_GAIN_TO_UNITY);

  popup->addSeparator();

  m->addCommandItem(popup, Command::AUDIO_PREFERENCES);
}

void addSelectMenu(Menus* m, PopupMenu* popup) {
  m->addCommandItem(popup, Command::SELECT_ALL);
  m->addCommandItem(popup, Command::DESELECT_ALL);
  m->addCommandItem(popup, Command::INVERT_LOOP_SELECTION);
  m->addCommandItem(popup, Command::TOGGLE_WHOLE_SONG_LOOP);

  popup->addSeparator();

  addBank(m, popup, Command::SELECT, "Select...");
  addBank(m, popup, Command::SELECT_ONLY, "Select Only...");
  addBank(m, popup, Command::TOGGLE, "Toggle...");
  addBank(m, popup, Command::UNSELECT, "Unselect...");
}

void addTransportMenu(Menus* m, PopupMenu* popup) {
  m->addCommandItem(popup, Command::TOGGLE_START_STOP);
  m->addCommandItem(popup, Command::ADD_LOOP_POINT);
  m->addCommandItem(popup, Command::CLEAR_LOOPS);

  popup->addSeparator();

  addBank(m, popup, Command::JUMP, "Jump To...");
  addBank(m, popup, Command::JUMP_SELECTED, "Jump To Selected...");
}

}  // namespace


const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  using command::Command;

  PopupMenu m;
  if (menuName == "File")
    addFileMenu(this, &m);

  else if (menuName == "Edit")
    addEditMenu(this, &m);

  else if (menuName == "Audio")
    addAudioMenu(this, &m);

  else if (menuName == "Select")
    addSelectMenu(this, &m);

  else if (menuName == "Transport")
    addTransportMenu(this, &m);

  return m;
}

}  // namespace slow
}  // namespace rec

