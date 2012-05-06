#include "rec/slow/AdvancedMenuMaker.h"

#include "rec/audio/AudioSettings.pb.h"
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
  addIfNotEmpty(Command::MUTE_VOLUME_TOGGLE);
  addIfNotEmpty(Command::DIM_VOLUME_TOGGLE);
  addIfNotEmpty(Command::NUDGE_VOLUME_UP);
  addIfNotEmpty(Command::NUDGE_VOLUME_DOWN);
  addIfNotEmpty(Command::RESET_GAIN_TO_UNITY);
  addIfNotEmpty(Command::TOGGLE_STRETCH_ENABLE);

  menu_.addSeparator();

  add(Command::AUDIO_PREFERENCES);
}

void AdvancedMenuMaker::addEditMenu() {
  BasicMenuMaker::addEditMenu();

  menu_.addSeparator();

  addIfNotEmpty(Command::MODE_SET_TIME);
  addIfNotEmpty(Command::MODE_DRAG);
  addIfNotEmpty(Command::MODE_ADD_LOOP_POINT);
  addIfNotEmpty(Command::MODE_ZOOM_IN);
}

void AdvancedMenuMaker::addFileMenu() {
  BasicMenuMaker::addFileMenu();

  menu_.addSeparator();

  addIfNotEmpty(Command::SAVE_FILE);
  addIfNotEmpty(Command::SAVE_FILE_SELECTION);

  PopupMenu save;
  int t = static_cast<int>(data::getGlobal<audio::AudioSettings>()
                           .file_type_for_save());
  static const int TICKED = ApplicationCommandInfo::isTicked;
  static const char* NAMES[] = {"AIFF", "FLAC", "Ogg Vorbis", "WAV"};
  static const Command::Type COMMAND = Command::SET_SAVE_FORMAT;
  for (int i = 0; i < audio::AudioSettings::COUNT; ++i)
    addRepeat(COMMAND, i, NAMES[i], &save, (i == t) ? TICKED : 0);

  menu_.addSubMenu(Trans("File Type For Save..."), save);
  menu_.addSeparator();

  add(Command::EXPORT_SETTINGS);
  add(Command::IMPORT_SETTINGS);
#ifdef NEW_FEATURES
  addIfNotEmpty(Command::CLEAR_SETTINGS_FOR_THIS_TRACK);
  add(Command::CLEAR_ALL_SETTINGS);
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
  addIfNotEmpty(Command::TOGGLE_PREFADER_LEVELS);

  menu_.addSeparator();

  addBank(Command::JUMP, Trans("Jump To..."));
  addBank(Command::JUMP_SELECTED, Trans("Jump To Selected..."));
}

void AdvancedMenuMaker::addHelpMenu() {
  BasicMenuMaker::addHelpMenu();

  menu_.addSeparator();
  add(Command::OPEN_SLOWGOLD_DIRECTORY);
  add(Command::CHECK_FOR_UPDATES);
  add(Command::TOGGLE_AUTOMATIC_UPDATES);
}

void AdvancedMenuMaker::addDisplayMenu() {
  add(Command::TOGGLE_GRID_DISPLAY);
  add(Command::TOGGLE_PARALLEL_WAVEFORMS);
  add(Command::TOGGLE_FOLLOW_CURSOR);
  menu_.addSeparator();
  add(Command::TOGGLE_SHOW_SELECTION_BUTTONS);
  add(Command::TOGGLE_SHOW_CURSOR_LABELS);
  menu_.addSeparator();
  add(Command::TOGGLE_SHOW_TIMES_AT_TOP);
  add(Command::TOGGLE_SHOW_LABELS_AT_TOP);
  add(Command::TOGGLE_COMMAND_BAR_AT_LEFT);
  add(Command::TOGGLE_COMMAND_BAR_AT_TOP);
  add(Command::TOGGLE_MODES_AT_LEFT);
  add(Command::TOGGLE_MODES_AT_TOP);
  menu_.addSeparator();
  add(Command::TOGGLE_FILE_OPEN_TREE_DISPLAY);
  add(Command::TOGGLE_SHOW_MASTER_TUNE);
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

