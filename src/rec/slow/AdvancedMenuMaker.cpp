#include "rec/slow/AdvancedMenuMaker.h"

#include "rec/base/ArraySize.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace slow {

using namespace rec::command;

void AdvancedMenuMaker::addEditMenu() {
  BasicMenuMaker::addEditMenu();

  addSeparator();

  addEnabled(slow::SlowCommand::COPY_ALL_LOOP_POINTS, !empty_);
  addEnabled(slow::SlowCommand::PASTE_OVER_LOOP_POINTS, !empty_);

  addSeparator();

  addEnabled(slow::SlowCommand::MODE_SET_TIME, !empty_);
  addEnabled(slow::SlowCommand::MODE_DRAG, !empty_);
  addEnabled(slow::SlowCommand::MODE_ADD_LOOP_POINT, !empty_);
  addEnabled(slow::SlowCommand::MODE_ZOOM_IN, !empty_);
}

void AdvancedMenuMaker::addFileMenu() {
  BasicMenuMaker::addFileMenu();

  addSeparator();
  addBasic(slow::SlowCommand::KEYBOARD_MAPPINGS);
  // addBasic(slow::SlowCommand::CLEAR_KEYBOARD_MAPPINGS);

  //addSeparator();
  addBasic(slow::SlowCommand::MIDI_MAPPINGS);
  //  addBasic(slow::SlowCommand::CLEAR_MIDI_MAPPINGS);

  addSeparator();
  addBasic(slow::SlowCommand::EXPORT_SETTINGS);
  addBasic(slow::SlowCommand::IMPORT_SETTINGS);
}

void AdvancedMenuMaker::addSelectMenu() {
  BasicMenuMaker::addSelectMenu();

  addSeparator();

  addBank(slow::SlowCommand::SELECT, Trans("Select..."));
  addBank(slow::SlowCommand::SELECT_ONLY, Trans("Select Only..."));
  addBank(slow::SlowCommand::TOGGLE_SELECTION, Trans("Toggle..."));
  addBank(slow::SlowCommand::UNSELECT, Trans("Unselect..."));
}

void AdvancedMenuMaker::addTransportMenu() {
  BasicMenuMaker::addTransportMenu();
  addEnabled(slow::SlowCommand::TOGGLE_PREFADER_LEVELS, !empty_);

  addSeparator();

  addBank(slow::SlowCommand::JUMP, Trans("Jump To..."));
  addBank(slow::SlowCommand::JUMP_SELECTED, Trans("Jump To Selected..."));

  addSeparator();
  addBasic(slow::SlowCommand::NUDGE_BACKWARD);
  addBasic(slow::SlowCommand::NUDGE_FORWARD);
}

void AdvancedMenuMaker::addHelpMenu() {
  BasicMenuMaker::addHelpMenu();
  addBasic(slow::SlowCommand::TOGGLE_SHOW_ABOUT_WINDOW_AT_STARTUP);

  addSeparator();
  addBasic(slow::SlowCommand::CHECK_FOR_UPDATES);
  addBasic(slow::SlowCommand::TOGGLE_AUTOMATIC_UPDATES);

#ifdef SETTINGS_MENU_ITEMS
  addSeparator();
  addBasic(slow::SlowCommand::OPEN_SLOWGOLD_DIRECTORY);
  addEnabled(slow::SlowCommand::CLEAR_SETTINGS_FOR_THIS_TRACK, !empty_);
  addBasic(slow::SlowCommand::CLEAR_ALL_SETTINGS);
#endif
}

void AdvancedMenuMaker::addDisplayMenu() {
  addBasic(slow::SlowCommand::TOGGLE_GRID_DISPLAY);
  addBasic(slow::SlowCommand::TOGGLE_PARALLEL_WAVEFORMS);
  addBasic(slow::SlowCommand::TOGGLE_FOLLOW_CURSOR);
  addSeparator();
  addBasic(slow::SlowCommand::TOGGLE_SHOW_SELECTION_BUTTONS);
  addBasic(slow::SlowCommand::TOGGLE_SHOW_CURSOR_LABELS);
  addSeparator();
  addBasic(slow::SlowCommand::TOGGLE_SHOW_TIMES_AT_TOP);
  addBasic(slow::SlowCommand::TOGGLE_SHOW_LABELS_AT_TOP);
  addBasic(slow::SlowCommand::TOGGLE_COMMAND_BAR_AT_LEFT);
  addBasic(slow::SlowCommand::TOGGLE_COMMAND_BAR_AT_TOP);
  addBasic(slow::SlowCommand::TOGGLE_MODES_AT_LEFT);
  addBasic(slow::SlowCommand::TOGGLE_MODES_AT_TOP);
  addSeparator();
  addBasic(slow::SlowCommand::TOGGLE_FILE_OPEN_TREE_DISPLAY);
  addBasic(slow::SlowCommand::TOGGLE_SHOW_MASTER_TUNE);
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

