#include "rec/slow/BasicMenuMaker.h"

#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/TargetManager.h"
#include "rec/gui/RecentFiles.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace slow {

using namespace rec::command;

void BasicMenuMaker::addFileMenu() {
  add(Command::OPEN);
  add(Command::CLOSE_FILE);
  add(Command::EJECT_CDS);

  menu_.addSeparator();

  // add(Command::CLEAR_NAVIGATOR);
  add(Command::KEYBOARD_MAPPINGS);
  add(Command::MIDI_MAPPINGS);
  add(Command::TOGGLE_ADVANCED_MENUS);

  std::vector<string> recent = rec::gui::getRecentFileNames();
  PopupMenu submenu;
  for (uint i = 0; i < recent.size(); ++i)
    addRepeat(Command::RECENT_FILES, i, str(recent[i]), true, &submenu);

  menu_.addSubMenu("Open recent", submenu);

#if !JUCE_MAC
  add(Command::ABOUT_THIS_PROGRAM);
  add(Command::QUIT);
#endif
}

void BasicMenuMaker::addEditMenu() {
  addEnabled(Command::UNDO, canUndo());
  addEnabled(Command::REDO, canRedo());

  menu_.addSeparator();

  addEnabled(Command::CUT, canCut());
  addEnabled(Command::COPY, canCopy());
  addEnabled(Command::PASTE, canPaste());

  menu_.addSeparator();

  add(Command::MODE_SET_TIME);
  add(Command::MODE_DRAG);
  add(Command::MODE_ADD_LOOP_POINT);
  add(Command::MODE_ZOOM_IN);

}

void BasicMenuMaker::addAudioMenu() {
  add(Command::MUTE_VOLUME_TOGGLE);
  add(Command::NUDGE_VOLUME_UP);
  add(Command::NUDGE_VOLUME_DOWN);
  add(Command::TOGGLE_STRETCH_ENABLE);

  menu_.addSeparator();

  add(Command::AUDIO_PREFERENCES);
}

void BasicMenuMaker::addSelectMenu() {
  add(Command::SELECT_ALL);
  add(Command::DESELECT_ALL);
  add(Command::INVERT_LOOP_SELECTION);
  add(Command::TOGGLE_WHOLE_SONG_LOOP);
}

void BasicMenuMaker::addTransportMenu() {
  add(Command::TOGGLE_START_STOP);
  add(Command::ADD_LOOP_POINT);
  add(Command::CLEAR_LOOPS);
}

const StringArray BasicMenuMaker::getMenuBarNames() const {
  static const char* NAMES[] = {"File", "Edit", "Audio", "Transport", "Select"};
  return StringArray(NAMES, arraysize(NAMES));
}

bool BasicMenuMaker::addMenu(const String& menuName) {
  if (menuName == "File")
    addFileMenu();

  else if (menuName == "Edit")
    addEditMenu();

  else if (menuName == "Audio")
    addAudioMenu();

  else if (menuName == "Select")
    addSelectMenu();

  else if (menuName == "Transport")
    addTransportMenu();

  else
    return false;
}

}  // namespace slow
}  // namespace rec

