#include "rec/slow/Menus.h"
#include "rec/base/ArraySize.h"
#include "rec/gui/RecentFiles.h"
#include "rec/util/Undo.h"
#include "rec/slow/Instance.h"
#include "rec/command/CommandIDEncoder.h"
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

namespace {

void addBank(TargetManager* t, PopupMenu* menu, Command::Type command,
             const String& name) {
  PopupMenu sub;
  for (int i = CommandIDEncoder::FIRST; i < SLOT_COUNT; ++i) {
    if (i == 0)
      sub.addSeparator();

    t->addCommandItem(&sub, CommandIDEncoder::toCommandID(i, command));
  }

  menu->addSubMenu(name, sub);
}

void addFileMenu(TargetManager* t, PopupMenu* popup) {
  t->addCommandItem(popup, Command::OPEN);
  t->addCommandItem(popup, Command::CLOSE_FILE);
  t->addCommandItem(popup, Command::EJECT_CDS);

  popup->addSeparator();

  // t->addCommandItem(popup, Command::CLEAR_NAVIGATOR);
  t->addCommandItem(popup, Command::KEYBOARD_MAPPINGS);
  t->addCommandItem(popup, Command::MIDI_MAPPINGS);

  std::vector<string> recent = rec::gui::getRecentFileNames();
  PopupMenu submenu;
  for (uint i = 0; i < recent.size(); ++i) {
    CommandID id = CommandIDEncoder::toCommandID(i, Command::RECENT_FILES);
    t->addCommandItem(&submenu, id, true, str(recent[i]));
  }

  popup->addSubMenu("Open recent", submenu);

#if !JUCE_MAC
    t->addCommandItem(&m, Command::QUIT);
#endif
}

void addEditMenu(TargetManager* t, PopupMenu* popup) {
  t->addCommandItem(popup, Command::UNDO, canUndo());
  t->addCommandItem(popup, Command::REDO, canRedo());

  popup->addSeparator();

  t->addCommandItem(popup, Command::CUT, canCut());
  t->addCommandItem(popup, Command::COPY, canCopy());
  t->addCommandItem(popup, Command::PASTE, canPaste());
}

void addAudioMenu(TargetManager* t, PopupMenu* popup) {
  t->addCommandItem(popup, Command::MUTE_VOLUME_TOGGLE);
  t->addCommandItem(popup, Command::DIM_VOLUME_TOGGLE);
  t->addCommandItem(popup, Command::NUDGE_VOLUME_UP);
  t->addCommandItem(popup, Command::NUDGE_VOLUME_DOWN);
  t->addCommandItem(popup, Command::RESET_GAIN_TO_UNITY);

  popup->addSeparator();

  t->addCommandItem(popup, Command::AUDIO_PREFERENCES);
}

void addSelectMenu(TargetManager* t, PopupMenu* popup) {
  t->addCommandItem(popup, Command::SELECT_ALL);
  t->addCommandItem(popup, Command::DESELECT_ALL);
  t->addCommandItem(popup, Command::INVERT_LOOP_SELECTION);
  t->addCommandItem(popup, Command::TOGGLE_WHOLE_SONG_LOOP);

  popup->addSeparator();

  addBank(t, popup, Command::SELECT, "Select...");
  addBank(t, popup, Command::SELECT_ONLY, "Select Only...");
  addBank(t, popup, Command::TOGGLE_SELECTION, "Toggle...");
  addBank(t, popup, Command::UNSELECT, "Unselect...");
}

void addTransportMenu(TargetManager* t, PopupMenu* popup) {
  t->addCommandItem(popup, Command::TOGGLE_START_STOP);
  t->addCommandItem(popup, Command::ADD_LOOP_POINT);
  t->addCommandItem(popup, Command::CLEAR_LOOPS);
  t->addCommandItem(popup, Command::TOGGLE_GRID_DISPLAY);

  popup->addSeparator();

  addBank(t, popup, Command::JUMP, "Jump To...");
  addBank(t, popup, Command::JUMP_SELECTED, "Jump To Selected...");
}

}  // namespace

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  using command::Command;

  PopupMenu m;
  TargetManager* t = target()->targetManager();
  if (menuName == "File")
    addFileMenu(t, &m);

  else if (menuName == "Edit")
    addEditMenu(t, &m);

  else if (menuName == "Audio")
    addAudioMenu(t, &m);

  else if (menuName == "Select")
    addSelectMenu(t, &m);

  else if (menuName == "Transport")
    addTransportMenu(t, &m);

  return m;
}

}  // namespace slow
}  // namespace rec

