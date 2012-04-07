#include "rec/slow/callbacks/GlobalCallbacks.h"

#include "rec/data/ZipData.h"
#include "rec/base/Trans.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"
#include "rec/util/cd/Eject.h"

namespace rec {
namespace slow {

namespace {

// TODO: this is duplicated in DownloadVersion
const String WOODSHED("http://www.worldwidewoodshed.com/slowgold/");
const String MANUAL = "SlowGoldManual.pdf";
const String FULL_MANUAL = WOODSHED + MANUAL;

Trans CANT_LOAD("Couldn't Load The SlowGold 8 User Manual");
Trans CANT_LOAD_FULL("Sorry, couldn't load the SlowGold 8 user manual at");
Trans CANT_SUPPORT("Couldn't Create A Support Request");
Trans CANT_SUPPORT_FULL("Sorry, we were unable to create a support request.");
Trans CLICK_TO_CONTINUE("Click to continue.");
Trans PLEASE_CONTACT("Please contact World Wide Woodshed support at");
Trans PLEASE_MAIL("Please mail the file to %s and then you can throw it away.");
Trans SUPPORTED("A Support Request Was Created On Your Desktop");
Trans SUPPORT_FULL("A Support Request file named %s "
                   "was created on your desktop.");

const String SUPPORT = "support@worldwidewoodshed.com";
const String MAILTO = "mailto:" + SUPPORT + "?subj=Support-Request";

using juce::AlertWindow;

void alert(const String& title, const String& msg) {
  AlertWindow::showMessageBox(AlertWindow::WarningIcon, title, msg +
                              PLEASE_CONTACT + "\n" + SUPPORT,
                              CLICK_TO_CONTINUE);
}

void openManual() {
  bool ok = juce::URL(FULL_MANUAL).launchInDefaultBrowser();
  if (!ok) {
    String m = CANT_LOAD_FULL + String(" ") + WOODSHED + "\n" + PLEASE_CONTACT;
    alert(CANT_LOAD, m);
  }
}

void requestSupport() {
  File f = data::zipData();
  if (f == File::nonexistent) {
    alert(CANT_SUPPORT, CANT_SUPPORT_FULL);
  } else {
    alert(SUPPORTED,
          String::formatted(SUPPORT_FULL, c_str(f.getFileName())) + "\n" +
          String::formatted(PLEASE_MAIL, c_str(SUPPORT)));

    juce::URL(MAILTO).launchInDefaultBrowser();
  }
}

}

using command::Command;

void addGlobalCallbacks(CommandRecordTable* t) {
  addCallback(t, Command::DEL, cutNoClipboard);
  addCallback(t, Command::CUT, cutToClipboard);
  addCallback(t, Command::COPY, copyToClipboard);
  addCallback(t, Command::PASTE, pasteFromClipboard);
  addCallback(t, Command::REDO, redo);
  addCallback(t, Command::UNDO, undo);
  addCallback(t, Command::EJECT_CDS, cd::ejectAll);
  addCallback(t, Command::OPEN_MANUAL, openManual);
  addCallback(t, Command::REQUEST_SUPPORT, requestSupport);
}

void GlobalCallbacks::translateAll() {
  CANT_LOAD.translate();
  CANT_LOAD.translate();
  CANT_LOAD_FULL.translate();
  CANT_LOAD_FULL.translate();
  CANT_SUPPORT.translate();
  CANT_SUPPORT.translate();
  CANT_SUPPORT_FULL.translate();
  CANT_SUPPORT_FULL.translate();
  CLICK_TO_CONTINUE.translate();
  CLICK_TO_CONTINUE.translate();
  PLEASE_CONTACT.translate();
  PLEASE_CONTACT.translate();
  PLEASE_MAIL.translate();
  PLEASE_MAIL.translate();
  SUPPORTED.translate();
  SUPPORTED.translate();
  SUPPORT_FULL.translate();
  SUPPORT_FULL.translate();
}

}  // namespace slow
}  // namespace rec
