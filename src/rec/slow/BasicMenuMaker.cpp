#include "rec/slow/BasicMenuMaker.h"

#include "rec/audio/AudioSettings.pb.h"
#include "rec/base/ArraySize.h"
#include "rec/data/DataOps.h"
#include "rec/gui/menu/RecentFiles.h"
#include "rec/slow/commands/SlowCommand.pb.h"
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
  nullptr, &t_GERMAN, &t_ENGLISH, &t_SPANISH, &t_FRENCH, &t_INDONESIAN
};

const Trans& langName(int lang) {
  return *(LANG_NAMES[lang]);
}

const int TICKED = ApplicationCommandInfo::isTicked;

void addRecentFileSubmenu(MenuMaker* maker) {
  vector<string> recent = rec::gui::getRecentFileNames();

  maker->addSeparator();
  maker->addEnabled(slow::SlowCommand::OPEN_PREVIOUS_FILE, !recent.empty());

  PopupMenu submenu;
  for (uint i = 0; i < recent.size(); ++i)
    maker->addRepeat(slow::SlowCommand::RECENT_FILES, i, str(recent[i]), &submenu);

  maker->menu()->addSubMenu(t_OPEN_RECENT, submenu, !recent.empty());
  maker->addSeparator();
}

void addSaveMenuEntries(MenuMaker* maker) {
#ifndef SLOWGOLD_SAVE_DISABLED
  maker->addEnabled(slow::SlowCommand::SAVE_FILE, !maker->empty());
  maker->addEnabled(slow::SlowCommand::SAVE_FILE_SELECTION, !maker->empty());

  PopupMenu save;
  int t = static_cast<int>(data::getProto<audio::AudioSettings>()
                           .file_type_for_save());
  static const char* NAMES[] = {"AIFF", "FLAC", "Ogg Vorbis", "WAV"};
  static const CommandID COMMAND = slow::SlowCommand::SET_SAVE_FORMAT;
  for (int i = 0; i < audio::AudioSettings::COUNT; ++i)
    maker->addRepeat(COMMAND, i, NAMES[i], &save, (i == t) ? TICKED : 0);

  maker->menu()->addSubMenu(t_FILE_TYPE_FOR_SAVE, save);
  maker->addSeparator();
#endif
}

void addLanguageSubmenu(MenuMaker* maker) {
#ifdef NEW_FEATURES
  Language lang = translation::getLanguage();
  PopupMenu menu;

  maker->addRepeat(slow::SlowCommand::SET_LANGUAGE, lang, String(langName(lang)),
                   &menu, TICKED);

  for (int i = app::AppSettings::FIRST; i <= app::AppSettings::LAST; ++i) {
    if (i != lang)
      maker->addRepeat(slow::SlowCommand::SET_LANGUAGE, i, String(langName(i)), &menu, 0);
  }
  maker->menu()->addSubMenu(t_LANGUAGE, menu);
#endif
}

}  // namespace

void BasicMenuMaker::addFileMenu() {
  addBasic(slow::SlowCommand::OPEN);
  addEnabled(slow::SlowCommand::CLOSE_FILE, !empty_);
  addBasic(slow::SlowCommand::EJECT_CDS);

  addSeparator();

  // addBasic(slow::SlowCommand::CLEAR_NAVIGATOR);
  addBasic(slow::SlowCommand::TOGGLE_ADVANCED_MENUS);

  addRecentFileSubmenu(this);
  addSaveMenuEntries(this);
  addLanguageSubmenu(this);

#if !JUCE_MAC
  addSeparator();

  addBasic(slow::SlowCommand::ABOUT_THIS_PROGRAM);
  addBasic(slow::SlowCommand::QUIT);
#endif
}

void BasicMenuMaker::addEditMenu() {
  addEnabled(slow::SlowCommand::UNDO, canUndo());
  addEnabled(slow::SlowCommand::REDO, canRedo());

  addSeparator();

  addEnabled(slow::SlowCommand::CUT, canCut());
  addEnabled(slow::SlowCommand::COPY, canCopy());
  addEnabled(slow::SlowCommand::PASTE, canPaste());
}

void BasicMenuMaker::addAudioMenu() {
  addEnabled(slow::SlowCommand::MUTE_VOLUME_TOGGLE, !empty_);
  addEnabled(slow::SlowCommand::NUDGE_VOLUME_UP, !empty_);
  addEnabled(slow::SlowCommand::NUDGE_VOLUME_DOWN, !empty_);

  addSeparator();

  addEnabled(slow::SlowCommand::TOGGLE_STRETCH_ENABLE, !empty_);
  addEnabled(slow::SlowCommand::NUDGE_SPEED_UP, !empty_);
  addEnabled(slow::SlowCommand::NUDGE_SPEED_DOWN, !empty_);

  addSeparator();

  addBasic(slow::SlowCommand::AUDIO_PREFERENCES);
}

void BasicMenuMaker::addSelectMenu() {
  addEnabled(slow::SlowCommand::SELECT_ALL, !empty_);
  addEnabled(slow::SlowCommand::DESELECT_ALL, !empty_);
  addEnabled(slow::SlowCommand::INVERT_LOOP_SELECTION, !empty_);

#ifdef NEW_FEATURES
  addSeparator();
  addEnabled(slow::SlowCommand::LOOP_NEXT_SEGMENT, !empty_);
#endif

  switch (isWholeSong_.isWholeSong()) {
   case IsWholeSong::ONE_SEGMENT:
    addEnabledName(slow::SlowCommand::TOGGLE_WHOLE_SONG_LOOP, !empty_,
                   t_LOOP_ENTIRE_TRACK);
    break;

   case IsWholeSong::WHOLE_SONG:
    addEnabledName(slow::SlowCommand::TOGGLE_WHOLE_SONG_LOOP, !empty_,
                   t_LOOP_THIS_SEGMENT);
    break;

   case IsWholeSong::SONG_IS_ONE_SEGMENT:
    addEnabledName(slow::SlowCommand::TOGGLE_WHOLE_SONG_LOOP, false,
                   t_LOOP_ENTIRE_TRACK);
    break;
  }

#ifdef NEW_FEATURES
  addSeparator();
#endif

  addEnabled(slow::SlowCommand::ZOOM_TO_SELECTION, !empty_);
}

void BasicMenuMaker::addTransportMenu() {
  addEnabled(slow::SlowCommand::TOGGLE_START_STOP, !empty_);
  addEnabled(slow::SlowCommand::ADD_LOOP_POINT, !empty_);
  addEnabled(slow::SlowCommand::CLEAR_LOOPS, !empty_);
}

void BasicMenuMaker::addHelpMenu() {
  addBasic(slow::SlowCommand::OPEN_MANUAL);
  addBasic(slow::SlowCommand::REQUEST_SUPPORT);
  addBasic(slow::SlowCommand::WHATS_NEW_PAGE);
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

