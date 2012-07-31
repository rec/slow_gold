#include "rec/command/map/CommandEntryWindow.h"
#include "rec/base/Trans.h"

namespace rec {
namespace command {

namespace {

TRTR(NEW_COMMAND_MAPPING, "New command mapping");
TRTR(OK, "OK");
TRTR(CANCEL, "Cancel");

}  // namespace

//==============================================================================
CommandEntryWindow::CommandEntryWindow(const String& caption)
    : AlertWindow (NEW_COMMAND_MAPPING, caption, AlertWindow::NoIcon) {
  addButton(OK, 1);
  addButton(CANCEL, 0);

  // Probably not needed in the general case but no harm...
  // (avoid return + escape keys getting processed by the buttons..)
  for (int i = getNumChildComponents(); --i >= 0;)
    getChildComponent (i)->setWantsKeyboardFocus (false);

  setWantsKeyboardFocus (true);
  grabKeyboardFocus();
}

void CommandEntryWindow::translateAll() {
  NEW_COMMAND_MAPPING.translate();
  OK.translate();
  CANCEL.translate();
}

}  // namespace command
}  // namespace rec

