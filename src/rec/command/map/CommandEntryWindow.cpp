#include "rec/command/map/CommandEntryWindow.h"
#include "rec/base/TranslatedString.h"

namespace rec {
namespace command {

namespace {

Trans NEW_COMMAND_MAPPING("New command mapping");

}  // namespace

//==============================================================================
CommandEntryWindow::CommandEntryWindow(const String& caption)
    : AlertWindow (NEW_COMMAND_MAPPING, caption, AlertWindow::NoIcon) {
  addButton(trans("Ok"), 1);
  addButton(trans("Cancel"), 0);

  // Probably not needed in the general case but no harm...
  // (avoid return + escape keys getting processed by the buttons..)
  for (int i = getNumChildComponents(); --i >= 0;)
    getChildComponent (i)->setWantsKeyboardFocus (false);

  setWantsKeyboardFocus (true);
  grabKeyboardFocus();
}

void CommandEntryWindow::translateAll() {
  NEW_COMMAND_MAPPING.translate();
}

}  // namespace command
}  // namespace rec

