#include "rec/slow/BasicMenuMaker.h"

#include "rec/audio/AudioSettings.pb.h"
#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/TargetManager.h"
#include "rec/data/DataOps.h"
#include "rec/gui/RecentFiles.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

namespace rec {
namespace slow {

using namespace rec::command;

void BasicMenuMaker::addFileMenu() {
  add(Command::OPEN);
  addIfNotEmpty(Command::CLOSE_FILE);
  add(Command::EJECT_CDS);

  menu_.addSeparator();

  // add(Command::CLEAR_NAVIGATOR);
  add(Command::TOGGLE_ADVANCED_MENUS);

  std::vector<string> recent = rec::gui::getRecentFileNames();

  menu_.addSeparator();
  add(Command::OPEN_PREVIOUS_FILE, "", !recent.empty());

  PopupMenu submenu;
  for (uint i = 0; i < recent.size(); ++i)
    addRepeat(Command::RECENT_FILES, i, str(recent[i]), &submenu);

  menu_.addSubMenu(Trans("Open recent"), submenu, !recent.empty());
  menu_.addSeparator();

#ifndef SLOWGOLD_SAVE_DISABLED
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
#endif

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
}

void BasicMenuMaker::addAudioMenu() {
  addIfNotEmpty(Command::MUTE_VOLUME_TOGGLE);
  addIfNotEmpty(Command::NUDGE_VOLUME_UP);
  addIfNotEmpty(Command::NUDGE_VOLUME_DOWN);

  menu_.addSeparator();
  addIfNotEmpty(Command::TOGGLE_STRETCH_ENABLE);
  addIfNotEmpty(Command::NUDGE_SPEED_UP);
  addIfNotEmpty(Command::NUDGE_SPEED_DOWN);

  menu_.addSeparator();

  add(Command::AUDIO_PREFERENCES);
}

void BasicMenuMaker::addSelectMenu() {
  addIfNotEmpty(Command::SELECT_ALL);
  addIfNotEmpty(Command::DESELECT_ALL);
  addIfNotEmpty(Command::INVERT_LOOP_SELECTION);

  switch (isWholeSong_.isWholeSong()) {
   case IsWholeSong::ONE_SEGMENT:
    add(Command::TOGGLE_WHOLE_SONG_LOOP, Trans("Loop Entire Track"), !empty_);
    break;

   case IsWholeSong::WHOLE_SONG:
    add(Command::TOGGLE_WHOLE_SONG_LOOP, Trans("Loop This Segment"), !empty_);
    break;

   case IsWholeSong::SONG_IS_ONE_SEGMENT:
    add(Command::TOGGLE_WHOLE_SONG_LOOP, Trans("Loop Entire Track"), false);
    break;
  }
  addIfNotEmpty(Command::ZOOM_TO_SELECTION);
}

void BasicMenuMaker::addTransportMenu() {
  addIfNotEmpty(Command::TOGGLE_START_STOP);
  addIfNotEmpty(Command::ADD_LOOP_POINT);
  addIfNotEmpty(Command::CLEAR_LOOPS);
}

void BasicMenuMaker::addHelpMenu() {
  add(Command::OPEN_MANUAL);
  add(Command::REQUEST_SUPPORT);
  add(Command::WHATS_NEW_PAGE);
}

const StringArray BasicMenuMaker::getMenuBarNames() const {
  StringArray res;

  res.add(Trans("File"));
  res.add(Trans("Edit"));
  res.add(Trans("Audio"));
  res.add(Trans("Transport"));
  res.add(Trans("Select"));
  res.add(Trans("Help"));

  return res;
}

bool BasicMenuMaker::addMenu(const String& menuName) {
  if (menuName == Trans("File"))
    addFileMenu();

  else if (menuName == Trans("Edit"))
    addEditMenu();

  else if (menuName == Trans("Audio"))
    addAudioMenu();

  else if (menuName == Trans("Select"))
    addSelectMenu();

  else if (menuName == Trans("Transport"))
    addTransportMenu();

  else if (menuName == Trans("Help"))
    addHelpMenu();

  else
    return false;

  return true;
}

}  // namespace slow
}  // namespace rec

