#include "rec/slow/callbacks/GlobalCallbacks.h"

// Delete when finished testing!
#define TEST_EWS

#include "rec/util/ews/EWS.h"

#include "rec/app/DownloadVersion.h"
#include "rec/app/Files.h"
#include "rec/base/Trans.h"
#include "rec/data/DataOps.h"
#include "rec/data/Undoable.h"
#include "rec/data/ZipData.h"
#include "rec/program/Program.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/slow/GuiSettings.h"
#include "rec/support/RequestSupport.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/Undo.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/cd/Eject.h"

TRAN(CANT_LOAD, "Couldn't Load The SlowGold 8 User Manual");
TRAN(CANT_LOAD_FULL, "Sorry, couldn't load the SlowGold 8 user manual at");
TRAN(CLICK_TO_CONTINUE, "Click to continue.");
TRAN(SELECT_EXPORT_FILE, "Select A File To Save Exported Settings");
TRAN(SELECT_EXPORT_KEYBOARD_FILE, "Select A File To Save Exported Keyboard Command Mappings");
TRAN(SELECT_EXPORT_MIDI_FILE, "Select A File To Save Exported MIDI Command Mappings");
TRAN(SELECT_IMPORT_FILE, "Select A Zip File Containing Exported Settings");
TRAN(SELECT_IMPORT_KEYBOARD_FILE, "Select A File Containing Keyboard Command Mappings");
TRAN(SELECT_IMPORT_MIDI_FILE, "Select A File Containing MIDI Command Mappings");

namespace rec {
namespace slow {

namespace {

using namespace juce;

// TODO: this is duplicated in DownloadVersion
const String MANUAL = "SlowGoldManual.pdf";
const String FULL_MANUAL = app::WOODSHED + MANUAL;
const String WHATS_NEW_URL = app::WOODSHED + "%s/whats-new.html";

const String SUPPORT = "support@worldwidewoodshed.com";
const URL MAILTO("mailto:" + URL::addEscapeChars(SUPPORT, true));

using juce::AlertWindow;

void alert(const String& title, const String& msg) {
  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
  DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

  AlertWindow::showMessageBox(AlertWindow::WarningIcon, title, msg,
                              t_CLICK_TO_CONTINUE);
}

void openManual() {
  bool ok = juce::URL(FULL_MANUAL).launchInDefaultBrowser();
  if (!ok) {
    String m = t_CANT_LOAD_FULL + String(" ") + app::WOODSHED + "\n\n";
    alert(t_CANT_LOAD, m + t_PLEASE_CONTACT + "\n" + SUPPORT);
  }
}

void openSlowGoldDirectory() {
  File f = app::getAppDirectory();
  string typeName = VirtualFile::default_instance().GetTypeName();
  File g = f.getChildFile(str(typeName));
  g.revealToUser();
}

void exportSettings() {
  File start = File::getSpecialLocation(File::userDesktopDirectory).
    getChildFile("SlowGold Export.zip");
  File file = browseForFile(t_SELECT_EXPORT_FILE, start, SAVE_FILE);
  if (file == File::nonexistent)
    return;

  file = data::zipData(file);
  if (file == File::nonexistent)
    return;  // TODO: report error - very unlikely.
  else
    file.revealToUser();
}

void importSettings() {
  File start = File::getSpecialLocation(File::userDesktopDirectory);
  File file = browseForFile(t_SELECT_IMPORT_FILE, start, OPEN_FILE);
  if (file != File::nonexistent)
    data::unzipData(file);
}

void importKeyboardMappings() {
}

void importMidiMappings() {
}

void exportKeyboardMappings() {
}

void exportMidiMappings() {
}

void setMode(Mode::Action action) {
  Mode mode;
  mode.set_click(action);
  data::setProto(mode, data::global());
}

void modeDrag() {
  setMode(Mode::DRAG);
}

void modeSetTime() {
  setMode(Mode::SET_TIME);
}

void modeZoomIn() {
  setMode(Mode::ZOOM_IN);
}

void modeAddLoopPoint() {
  setMode(Mode::DRAW_LOOP_POINTS);
}

void whatsNewPage() {
#ifdef TEST_EWS
  CHECK(ews::confirm(ews::TEST_SERIAL_NUMBER));
#else
  const String& vers = JUCEApplication::getInstance()->getApplicationVersion();
  URL(String::formatted(WHATS_NEW_URL, c_str(vers))).launchInDefaultBrowser();
#endif
}

}  // namespace

void addGlobalCallbacks(program::Program* t) {
  addCallback(t, Command::MODE_ADD_LOOP_POINT, modeAddLoopPoint);
  addCallback(t, Command::MODE_DRAG, modeDrag);
  addCallback(t, Command::MODE_SET_TIME, modeSetTime);
  addCallback(t, Command::MODE_ZOOM_IN, modeZoomIn);
  addCallback(t, Command::COPY, copyToClipboard);
  addCallback(t, Command::CUT, cutToClipboard);
  addCallback(t, Command::DEL, cutNoClipboard);
  addCallback(t, Command::EJECT_CDS, cd::ejectAll);
  addCallback(t, Command::EXPORT_KEYBOARD_MAPPINGS, exportKeyboardMappings);
  addCallback(t, Command::EXPORT_MIDI_MAPPINGS, exportMidiMappings);
  addCallback(t, Command::EXPORT_SETTINGS, exportSettings);
  addCallback(t, Command::IMPORT_KEYBOARD_MAPPINGS, importKeyboardMappings);
  addCallback(t, Command::IMPORT_MIDI_MAPPINGS, importMidiMappings);
  addCallback(t, Command::IMPORT_SETTINGS, importSettings);
  addCallback(t, Command::OPEN_MANUAL, openManual);
  addCallback(t, Command::OPEN_SLOWGOLD_DIRECTORY, openSlowGoldDirectory);
  addCallback(t, Command::PASTE, pasteFromClipboard);
  addCallback(t, Command::REDO, redo);
  addCallback(t, Command::REQUEST_SUPPORT, support::requestSupport);
  addCallback(t, Command::UNDO, undo);
  addCallback(t, Command::WHATS_NEW_PAGE, whatsNewPage);
}


}  // namespace slow
}  // namespace rec
