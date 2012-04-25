#include "rec/slow/AdvancedMenuMaker.h"

#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/TargetManager.h"
#include "rec/data/DataOps.h"
#include "rec/gui/RecentFiles.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace slow {

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

void AdvancedMenuMaker::addFileMenu() {
  BasicMenuMaker::addFileMenu();

#ifdef NEW_FEATURES
  VirtualFile f = data::getGlobal<VirtualFile>();
  bool empty = file::empty(f);
  add(Command::SAVE_FILE, "", !empty);
  add(Command::SAVE_FILE_SELECTION, "", !empty);

  PopupMenu save;
  int t = static_cast<int>(data::getGlobal<GuiSettings>().file_type_for_save());
  static const int TICKED = ApplicationCommandInfo::isTicked;
  static const char* NAMES[] = {"AIFF", "FLAC", "Ogg Vorbis", "WAV"};
  static const Command::Type COMMAND = Command::SET_SAVE_FORMAT;
  for (int i = 0; i < GuiSettings::COUNT; ++i)
    addRepeat(COMMAND, i, NAMES[i], true, &save, (i == t) ? TICKED : 0);

  menu_.addSubMenu(Trans("File Type For Save..."), save);
#endif
}

void AdvancedMenuMaker::addSelectMenu() {
  BasicMenuMaker::addSelectMenu();

  menu_.addSeparator();

  addBank(Command::SELECT, Trans("Select..."));
  addBank(Command::SELECT_ONLY, Trans("Select Only..."));
  addBank(Command::TOGGLE_SELECTION, Trans("Toggle..."));
  addBank(Command::UNSELECT, Trans("Unselect..."));
}

void AdvancedMenuMaker::addTransportMenu() {
  BasicMenuMaker::addTransportMenu();
  add(Command::TOGGLE_PREFADER_LEVELS);

  menu_.addSeparator();

  addBank(Command::JUMP, Trans("Jump To..."));
  addBank(Command::JUMP_SELECTED, Trans("Jump To Selected..."));
}

void AdvancedMenuMaker::addDisplayMenu() {
  add(Command::TOGGLE_GRID_DISPLAY);
  add(Command::TOGGLE_FILE_OPEN_TREE_DISPLAY);
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

