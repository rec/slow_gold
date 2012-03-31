#include "rec/slow/AdvancedMenuMaker.h"

#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/TargetManager.h"
#include "rec/gui/RecentFiles.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace slow {

// i18n

using namespace rec::command;

void AdvancedMenuMaker::addAudioMenu() {
  add(Command::MUTE_VOLUME_TOGGLE);
  add(Command::DIM_VOLUME_TOGGLE);
  add(Command::NUDGE_VOLUME_UP);
  add(Command::NUDGE_VOLUME_DOWN);
  add(Command::RESET_GAIN_TO_UNITY);
  add(Command::TOGGLE_STRETCH_ENABLE);

  menu_.addSeparator();

  add(Command::AUDIO_PREFERENCES);
}

void AdvancedMenuMaker::addEditMenu() {
  BasicMenuMaker::addEditMenu();

  menu_.addSeparator();

  add(Command::MODE_SET_TIME);
  add(Command::MODE_DRAG);
  add(Command::MODE_ADD_LOOP_POINT);
  add(Command::MODE_ZOOM_IN);
}

void AdvancedMenuMaker::addSelectMenu() {
  BasicMenuMaker::addSelectMenu();

  menu_.addSeparator();

  addBank(Command::SELECT, "Select...");
  addBank(Command::SELECT_ONLY, "Select Only...");
  addBank(Command::TOGGLE_SELECTION, "Toggle...");
  addBank(Command::UNSELECT, "Unselect...");
}

void AdvancedMenuMaker::addTransportMenu() {
  BasicMenuMaker::addTransportMenu();
  add(Command::TOGGLE_PREFADER_LEVELS);

  menu_.addSeparator();

  addBank(Command::JUMP, "Jump To...");
  addBank(Command::JUMP_SELECTED, "Jump To Selected...");
}

void AdvancedMenuMaker::addDisplayMenu() {
  add(Command::TOGGLE_GRID_DISPLAY);
  add(Command::TOGGLE_PARALLEL_WAVEFORMS);
  add(Command::TOGGLE_FOLLOW_CURSOR);
  add(Command::TOGGLE_SHOW_SELECTION_BUTTONS);
  add(Command::TOGGLE_SHOW_CURSOR_LABELS);
  add(Command::TOGGLE_SHOW_TIMES_AT_TOP);
  add(Command::TOGGLE_SHOW_LABELS_AT_TOP);
  add(Command::TOGGLE_COMMAND_BAR_AT_LEFT);
  add(Command::TOGGLE_COMMAND_BAR_AT_TOP);
  add(Command::TOGGLE_MODES_AT_LEFT);
  add(Command::TOGGLE_MODES_AT_TOP);
}

const StringArray AdvancedMenuMaker::getMenuBarNames() const {
  static const char* NAMES[] = {"File", "Edit", "Audio", "Transport", "Select",
                                "Display", "Help"};
  return StringArray(NAMES, arraysize(NAMES));
}

bool AdvancedMenuMaker::addMenu(const String& menuName) {
  if (BasicMenuMaker::addMenu(menuName))
    return true;

  if (menuName == "Display")
    addDisplayMenu();

  else
    return false;

  return true;
}

}  // namespace slow
}  // namespace rec

