#include "rec/slow/BasicMenuMaker.h"

#include "rec/audio/AudioSettings.pb.h"
#include "rec/base/ArraySize.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/TargetManager.h"
#include "rec/data/DataOps.h"
#include "rec/gui/RecentFiles.h"
#include "rec/translation/TranslationTables.h"
#include "rec/util/Cuttable.h"
#include "rec/util/STL.h"
#include "rec/util/Undo.h"

TRAN(LANGUAGE, "Language");

TRAN(ENGLISH, "English");
TRAN(FRENCH, "French");
TRAN(GERMAN, "German");
TRAN(INDONESIAN, "Indonesian");
TRAN(SPANISH, "Spanish");

TRAN(OPEN_RECENT, "Open recent");
TRAN(FILE_TYPE_FOR_SAVE, "File Type For Save...");

TRAN(LOOP_ENTIRE_TRACK, "Loop Entire Track");
TRAN(LOOP_THIS_SEGMENT, "Loop This Segment");

TRAN(FILE, "File");
TRAN(EDIT, "Edit");
TRAN(AUDIO, "Audio");
TRAN(TRANSPORT, "Transport");
TRAN(SELECT, "Select");
TRAN(HELP, "Help");

namespace rec {
namespace slow {

using namespace rec::command;

namespace {

const Trans* LANG_NAMES[] = {
  NULL, &t_GERMAN, &t_ENGLISH, &t_SPANISH, &t_FRENCH, &t_INDONESIAN
};

const Trans& langName(int lang) {
  return *(LANG_NAMES[lang]);
}

}  // namespace

void BasicMenuMaker::addFileMenu() {
  addBasic(Command::OPEN);
  addEnabled(Command::CLOSE_FILE, !empty_);
  addBasic(Command::EJECT_CDS);

  menu_.addSeparator();

  // addBasic(Command::CLEAR_NAVIGATOR);
  addBasic(Command::TOGGLE_ADVANCED_MENUS);

  std::vector<string> recent = rec::gui::getRecentFileNames();

  menu_.addSeparator();
  addEnabled(Command::OPEN_PREVIOUS_FILE, !recent.empty());

  PopupMenu submenu;
  for (uint i = 0; i < recent.size(); ++i)
    addRepeat(Command::RECENT_FILES, i, str(recent[i]), &submenu);

  menu_.addSubMenu(t_OPEN_RECENT, submenu, !recent.empty());
  menu_.addSeparator();

#ifndef SLOWGOLD_SAVE_DISABLED
  addEnabled(Command::SAVE_FILE, !empty_);
  addEnabled(Command::SAVE_FILE_SELECTION, !empty_);

  PopupMenu save;
  int t = static_cast<int>(data::getProto<audio::AudioSettings>()
                           .file_type_for_save());
  static const int TICKED = ApplicationCommandInfo::isTicked;
  static const char* NAMES[] = {"AIFF", "FLAC", "Ogg Vorbis", "WAV"};
  static const Command::Type COMMAND = Command::SET_SAVE_FORMAT;
  for (int i = 0; i < audio::AudioSettings::COUNT; ++i)
    addRepeat(COMMAND, i, NAMES[i], &save, (i == t) ? TICKED : 0);

  menu_.addSubMenu(t_FILE_TYPE_FOR_SAVE, save);
  menu_.addSeparator();
#endif

#ifdef NEW_FEATURES
  Language lang = translation::getLanguage();
  PopupMenu langMenu;

  addRepeat(Command::SET_LANGUAGE, lang, String(langName(lang)), &langMenu, TICKED);

  for (int i = app::AppSettings::FIRST; i <= app::AppSettings::LAST; ++i) {
    if (i != lang)
      addRepeat(Command::SET_LANGUAGE, i, String(langName(i)), &langMenu, 0);
  }
  menu_.addSubMenu(t_LANGUAGE, langMenu);
#endif

#if !JUCE_MAC
  menu_.addSeparator();

  addBasic(Command::ABOUT_THIS_PROGRAM);
  addBasic(Command::QUIT);
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
  addEnabled(Command::MUTE_VOLUME_TOGGLE, !empty_);
  addEnabled(Command::NUDGE_VOLUME_UP, !empty_);
  addEnabled(Command::NUDGE_VOLUME_DOWN, !empty_);

  menu_.addSeparator();
  addEnabled(Command::TOGGLE_STRETCH_ENABLE, !empty_);
  addEnabled(Command::NUDGE_SPEED_UP, !empty_);
  addEnabled(Command::NUDGE_SPEED_DOWN, !empty_);

  menu_.addSeparator();

  addBasic(Command::AUDIO_PREFERENCES);
}

void BasicMenuMaker::addSelectMenu() {
  addEnabled(Command::SELECT_ALL, !empty_);
  addEnabled(Command::DESELECT_ALL, !empty_);
  addEnabled(Command::INVERT_LOOP_SELECTION, !empty_);

#ifdef NEW_FEATURES
  menu_.addSeparator();
  addEnabled(Command::LOOP_NEXT_SEGMENT, !empty_);
#endif

  switch (isWholeSong_.isWholeSong()) {
   case IsWholeSong::ONE_SEGMENT:
    addEnabledName(Command::TOGGLE_WHOLE_SONG_LOOP, !empty_,
                   t_LOOP_ENTIRE_TRACK);
    break;

   case IsWholeSong::WHOLE_SONG:
    addEnabledName(Command::TOGGLE_WHOLE_SONG_LOOP, !empty_,
                   t_LOOP_THIS_SEGMENT);
    break;

   case IsWholeSong::SONG_IS_ONE_SEGMENT:
    addEnabledName(Command::TOGGLE_WHOLE_SONG_LOOP, false,
                   t_LOOP_ENTIRE_TRACK);
    break;
  }

#ifdef NEW_FEATURES
  menu_.addSeparator();
#endif

  addEnabled(Command::ZOOM_TO_SELECTION, !empty_);
}

void BasicMenuMaker::addTransportMenu() {
  addEnabled(Command::TOGGLE_START_STOP, !empty_);
  addEnabled(Command::ADD_LOOP_POINT, !empty_);
  addEnabled(Command::CLEAR_LOOPS, !empty_);
}

void BasicMenuMaker::addHelpMenu() {
  addBasic(Command::OPEN_MANUAL);
  addBasic(Command::REQUEST_SUPPORT);
  addBasic(Command::WHATS_NEW_PAGE);
}

const StringArray BasicMenuMaker::getMenuBarNames() const {
  StringArray res;

  res.add(t_FILE);
  res.add(t_EDIT);
  res.add(t_AUDIO);
  res.add(t_TRANSPORT);
  res.add(t_SELECT);
  res.add(t_HELP);

  return res;
}

bool BasicMenuMaker::addMenu(const String& menuName) {
  if (menuName == t_FILE)
    addFileMenu();

  else if (menuName == t_EDIT)
    addEditMenu();

  else if (menuName == t_AUDIO)
    addAudioMenu();

  else if (menuName == t_SELECT)
    addSelectMenu();

  else if (menuName == t_TRANSPORT)
    addTransportMenu();

  else if (menuName == t_HELP)
    addHelpMenu();

  else
    return false;

  return true;
}

}  // namespace slow
}  // namespace rec

