#include "rec/slow/AdvancedMenuMaker.h"

#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Target.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace slow {

using namespace rec::command;

void AdvancedMenuMaker::addEditMenu() {
  BasicMenuMaker::addEditMenu();

  addSeparator();

  addEnabled(Command::COPY_ALL_LOOP_POINTS, !empty_);
  addEnabled(Command::PASTE_OVER_LOOP_POINTS, !empty_);

  addSeparator();

  addEnabled(Command::MODE_SET_TIME, !empty_);
  addEnabled(Command::MODE_DRAG, !empty_);
  addEnabled(Command::MODE_ADD_LOOP_POINT, !empty_);
  addEnabled(Command::MODE_ZOOM_IN, !empty_);
}

void AdvancedMenuMaker::addFileMenu() {
  BasicMenuMaker::addFileMenu();

  addSeparator();
  addBasic(Command::KEYBOARD_MAPPINGS);
  // addBasic(Command::CLEAR_KEYBOARD_MAPPINGS);

  //addSeparator();
  addBasic(Command::MIDI_MAPPINGS);
  //  addBasic(Command::CLEAR_MIDI_MAPPINGS);

  addSeparator();
  addBasic(Command::EXPORT_SETTINGS);
  addBasic(Command::IMPORT_SETTINGS);
}

void AdvancedMenuMaker::addSelectMenu() {
  BasicMenuMaker::addSelectMenu();

  addSeparator();

  addBank(Command::SELECT, Trans("Select..."));
  addBank(Command::SELECT_ONLY, Trans("Select Only..."));
  addBank(Command::TOGGLE_SELECTION, Trans("Toggle..."));
  addBank(Command::UNSELECT, Trans("Unselect..."));
}

void AdvancedMenuMaker::addTransportMenu() {
  BasicMenuMaker::addTransportMenu();
  addEnabled(Command::TOGGLE_PREFADER_LEVELS, !empty_);

  addSeparator();

  addBank(Command::JUMP, Trans("Jump To..."));
  addBank(Command::JUMP_SELECTED, Trans("Jump To Selected..."));

  addSeparator();
  addBasic(Command::NUDGE_BACKWARD);
  addBasic(Command::NUDGE_FORWARD);
}

void AdvancedMenuMaker::addHelpMenu() {
  BasicMenuMaker::addHelpMenu();
  addBasic(Command::TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP);

  addSeparator();
  addBasic(Command::CHECK_FOR_UPDATES);
  addBasic(Command::TOGGLE_AUTOMATIC_UPDATES);

#ifdef SETTINGS_MENU_ITEMS
  addSeparator();
  addBasic(Command::OPEN_SLOWGOLD_DIRECTORY);
  addEnabled(Command::CLEAR_SETTINGS_FOR_THIS_TRACK, !empty_);
  addBasic(Command::CLEAR_ALL_SETTINGS);
#endif
}

void AdvancedMenuMaker::addDisplayMenu() {
  addBasic(Command::TOGGLE_GRID_DISPLAY);
  addBasic(Command::TOGGLE_PARALLEL_WAVEFORMS);
  addBasic(Command::TOGGLE_FOLLOW_CURSOR);
  addSeparator();
  addBasic(Command::TOGGLE_SHOW_SELECTION_BUTTONS);
  addBasic(Command::TOGGLE_SHOW_CURSOR_LABELS);
  addSeparator();
  addBasic(Command::TOGGLE_SHOW_TIMES_AT_TOP);
  addBasic(Command::TOGGLE_SHOW_LABELS_AT_TOP);
  addBasic(Command::TOGGLE_COMMAND_BAR_AT_LEFT);
  addBasic(Command::TOGGLE_COMMAND_BAR_AT_TOP);
  addBasic(Command::TOGGLE_MODES_AT_LEFT);
  addBasic(Command::TOGGLE_MODES_AT_TOP);
  addSeparator();
  addBasic(Command::TOGGLE_FILE_OPEN_TREE_DISPLAY);
  addBasic(Command::TOGGLE_SHOW_MASTER_TUNE);
}

const StringArray AdvancedMenuMaker::getMenuBarNames() const {
  StringArray res;

  res.add(Trans("File"));
  res.add(Trans("Edit"));
  res.add(Trans("Audio"));
  res.add(Trans("Transport"));
  res.add(Trans("Select"));
  res.add(Trans("Display"));
  res.add(Trans("Help"));

  return res;
}

bool AdvancedMenuMaker::addMenu(const String& menuName) {
  if (BasicMenuMaker::addMenu(menuName))
    return true;

  if (menuName == Trans("Display"))
    addDisplayMenu();

  else
    return false;

  return true;
}

}  // namespace slow
}  // namespace rec

