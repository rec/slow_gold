#include "rec/slow/callbacks/GlobalCallbacks.h"

#include "rec/app/Files.h"
#include "rec/base/Trans.h"
#include "rec/data/DataOps.h"
#include "rec/data/ZipData.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/GuiSettings.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/Undo.h"
#include "rec/util/cd/Eject.h"

namespace rec {
namespace slow {

namespace {

using namespace juce;

// TODO: this is duplicated in DownloadVersion
const String WOODSHED("http://www.worldwidewoodshed.com/slowgold/");
const String MANUAL = "SlowGoldManual.pdf";
const String FULL_MANUAL = WOODSHED + MANUAL;
const String WHATS_NEW_URL = WOODSHED + "%s/whats-new.html";

Trans CANT_LOAD("Couldn't Load The SlowGold 8 User Manual");
Trans CANT_LOAD_FULL("Sorry, couldn't load the SlowGold 8 user manual at");
Trans CANT_SUPPORT("Couldn't Create A Support Request");
Trans CANT_SUPPORT_FULL("Sorry, we were unable to create a support request.");
Trans CLICK_TO_CONTINUE("Click to continue.");
Trans MAIL_ATTACH("Please attach the file on your desktop named %s to this "
                  "email and send it to us!");
Trans MAIL_CREATED("A Support Request file named \"%s\" "
                   "was created on your desktop.");
Trans MAIL_DISCARD("You can throw the file away once your email is sent.");
Trans MAIL_SUBJECT("Support Request: %s");
Trans PLEASE_CONTACT("Please contact World Wide Woodshed support at");
Trans PLEASE_MAIL("Please mail the file to %s and then you can throw it away.");
Trans SUPPORTED("A Support Request Was Created On Your Desktop");
Trans SELECT_EXPORT_FILE("Select A File To Save Exported Settings");
Trans SELECT_EXPORT_KEYBOARD_FILE("Select A File To Save Exported Keyboard Command Mappings");
Trans SELECT_EXPORT_MIDI_FILE("Select A File To Save Exported MIDI Command Mappings");
Trans SELECT_IMPORT_FILE("Select A Zip File Containing Exported Settings");
Trans SELECT_IMPORT_KEYBOARD_FILE("Select A File Containing Keyboard Command Mappings");
Trans SELECT_IMPORT_MIDI_FILE("Select A File Containing MIDI Command Mappings");

const String SUPPORT = "support@worldwidewoodshed.com";
const URL MAILTO("mailto:" + URL::addEscapeChars(SUPPORT, true));

using juce::AlertWindow;

void alert(const String& title, const String& msg) {
  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);
  DCHECK(LookAndFeel::getDefaultLookAndFeel().isUsingNativeAlertWindows());

  AlertWindow::showMessageBox(AlertWindow::WarningIcon, title, msg,
                              CLICK_TO_CONTINUE);
}

const char* const VOWELS = "aeiouy";
const char* const CONSONANTS = "bdfgjlmnprsvwxz";
const char* const LETTERS[] = {VOWELS, CONSONANTS};
const uint32 LENGTHS[] = {strlen(VOWELS), strlen(CONSONANTS)};

const int LENGTH = 10;

String randomKey(int length = LENGTH) {
  String s;
  Random random;
  int index = random.nextInt(2);
  for (int i = 0; i < length; ++i, index = 1 - index)
    s += LETTERS[index][random.nextInt(LENGTHS[index])];

  return s;
}

void openManual() {
  bool ok = juce::URL(FULL_MANUAL).launchInDefaultBrowser();
  if (!ok) {
    String m = CANT_LOAD_FULL + String(" ") + WOODSHED + "\n\n";
    alert(CANT_LOAD, m + PLEASE_CONTACT + "\n" + SUPPORT);
  }
}

void openSlowGoldDirectory() {
  File f = app::getAppDirectory();
  string typeName = VirtualFile::default_instance().GetTypeName();
  File g = f.getChildFile(str(typeName));
  g.revealToUser();
}

void requestSupport() {
  String key = randomKey();
  File f = data::zipData(key);
  if (f == File::nonexistent) {
    alert(CANT_SUPPORT, CANT_SUPPORT_FULL + String("\n") +
          PLEASE_CONTACT + String("\n") + SUPPORT);
  } else {
    String fn = f.getFileName();
    alert(SUPPORTED,
          String::formatted(MAIL_CREATED, c_str(fn)) + "\n\n" +
          String::formatted(PLEASE_MAIL, c_str(SUPPORT)));
    String subject = String::formatted(MAIL_SUBJECT, c_str(key));
    String body = String::formatted(MAIL_ATTACH, c_str(fn)) + String("\n\n") +
      MAIL_DISCARD;
    URL url = MAILTO.withParameter("subject", subject).withParameter("body", body);
    url.launchInDefaultBrowser();
    f.revealToUser();
  }
}

void exportSettings() {
  File start = File::getSpecialLocation(File::userDesktopDirectory).
    getChildFile("SlowGold Export.zip");
  File file = browseForFile(SELECT_EXPORT_FILE, start, SAVE_FILE);
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
  File file = browseForFile(SELECT_IMPORT_FILE, start, OPEN_FILE);
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
  const String& vers = JUCEApplication::getInstance()->getApplicationVersion();
  URL(String::formatted(WHATS_NEW_URL, c_str(vers))).launchInDefaultBrowser();
}

}

using command::Command;

void addGlobalCallbacks(CommandRecordTable* t) {
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
  addCallback(t, Command::REQUEST_SUPPORT, requestSupport);
  addCallback(t, Command::UNDO, undo);
  addCallback(t, Command::WHATS_NEW_PAGE, whatsNewPage);
}

void GlobalCallbacks::translateAll() {
  CANT_LOAD.translate();
  CANT_LOAD_FULL.translate();
  CANT_SUPPORT.translate();
  CANT_SUPPORT_FULL.translate();
  CLICK_TO_CONTINUE.translate();
  MAIL_ATTACH.translate();
  MAIL_CREATED.translate();
  MAIL_DISCARD.translate();
  MAIL_SUBJECT.translate();
  PLEASE_CONTACT.translate();
  PLEASE_MAIL.translate();
  SELECT_EXPORT_FILE.translate();
  SELECT_EXPORT_KEYBOARD_FILE.translate();
  SELECT_EXPORT_MIDI_FILE.translate();
  SELECT_IMPORT_FILE.translate();
  SELECT_IMPORT_KEYBOARD_FILE.translate();
  SELECT_IMPORT_MIDI_FILE.translate();
  SUPPORTED.translate();
}

}  // namespace slow
}  // namespace rec
