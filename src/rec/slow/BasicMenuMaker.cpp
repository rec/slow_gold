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

#ifdef NEW_FEATURES
  PopupMenu savemenu;
  add(Command::SAVE_AS_AIFF, String::empty, true, &savemenu);
  add(Command::SAVE_AS_FLAC, String::empty, true, &savemenu);
  add(Command::SAVE_AS_MP3, String::empty, true, &savemenu);
  add(Command::SAVE_AS_OGG, String::empty, true, &savemenu);
  add(Command::SAVE_AS_WAV, String::empty, true, &savemenu);

  menu_.addSubMenu(Trans("Save..."), savemenu);

  PopupMenu saveselmenu;
  add(Command::SAVE_SELECTION_AS_AIFF, String::empty, true, &saveselmenu);
  add(Command::SAVE_SELECTION_AS_FLAC, String::empty, true, &saveselmenu);
  add(Command::SAVE_SELECTION_AS_MP3, String::empty, true, &saveselmenu);
  add(Command::SAVE_SELECTION_AS_OGG, String::empty, true, &saveselmenu);
  add(Command::SAVE_SELECTION_AS_WAV, String::empty, true, &saveselmenu);

  menu_.addSubMenu(Trans("Save Selection..."), saveselmenu);
#endif

  std::vector<string> recent = rec::gui::getRecentFileNames();
  PopupMenu submenu;
  for (uint i = 0; i < recent.size(); ++i)
    addRepeat(Command::RECENT_FILES, i, str(recent[i]), true, &submenu);

  menu_.addSubMenu(Trans("Open recent"), submenu);

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

  switch (isWholeSong_.isWholeSong()) {
   case IsWholeSong::ONE_SEGMENT:
    add(Command::TOGGLE_WHOLE_SONG_LOOP, Trans("Loop Entire Track"));
    break;

   case IsWholeSong::WHOLE_SONG:
    add(Command::TOGGLE_WHOLE_SONG_LOOP, Trans("Loop This Segment"));
    break;

   case IsWholeSong::SONG_IS_ONE_SEGMENT:
    add(Command::TOGGLE_WHOLE_SONG_LOOP, Trans("Loop Entire Track"), false);
    break;
  }
  add(Command::ZOOM_TO_SELECTION);
}

void BasicMenuMaker::addTransportMenu() {
  add(Command::TOGGLE_START_STOP);
  add(Command::ADD_LOOP_POINT);
  add(Command::CLEAR_LOOPS);
}

void BasicMenuMaker::addHelpMenu() {
  add(Command::OPEN_MANUAL);
  add(Command::REQUEST_SUPPORT);
  add(Command::CHECK_FOR_UPDATES);
  add(Command::TOGGLE_AUTOMATIC_UPDATES);
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

