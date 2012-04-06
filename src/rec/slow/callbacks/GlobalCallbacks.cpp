#include "rec/slow/callbacks/GlobalCallbacks.h"

#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"
#include "rec/util/cd/Eject.h"
#include "rec/base/Trans.h"

namespace rec {
namespace slow {

namespace {

// TODO: this is duplicated in DownloadVersion
const String WOODSHED("http://www.worldwidewoodshed.com/slowgold/");
const String MANUAL = "SlowGoldManual.pdf";
const String FULL_MANUAL = WOODSHED + MANUAL;

Trans CANT_LOAD("Sorry, couldn't load the SlowGold 8 user manual");
Trans AT("at");
Trans PLEASE_CONTACT("Please contact World Wide Woodshed support.");
Trans CLICK_TO_CONTINUE("Click to continue.");

using juce::AlertWindow;

void openManual() {
  bool ok = juce::URL(FULL_MANUAL).launchInDefaultBrowser();
  if (!ok) {
    AlertWindow::showMessageBox(
        AlertWindow::WarningIcon,
        CANT_LOAD,
        CANT_LOAD + String(" ") + String(AT) + String(" ") + WOODSHED + "\n" +
        PLEASE_CONTACT,
        CLICK_TO_CONTINUE);
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
  addCallback(t, Command::EJECT_CDS, &cd::ejectAll);
  addCallback(t, Command::OPEN_MANUAL, &openManual);
}

void GlobalCallbacks::translateAll() {
  CANT_LOAD.translate();
  AT.translate();
  PLEASE_CONTACT.translate();
  CLICK_TO_CONTINUE.translate();
}

}  // namespace slow
}  // namespace rec
