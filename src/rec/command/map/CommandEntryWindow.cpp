#include "rec/command/map/CommandEntryWindow.h"
#include "rec/base/Trans.h"

TRAN(NEW_COMMAND_MAPPING, "New command mapping");

namespace rec {
namespace command {

CommandEntryWindow::CommandEntryWindow(const String& caption,
                                       CommandMapEditor* editor)
    : AlertWindow (t_NEW_COMMAND_MAPPING, caption, AlertWindow::NoIcon),
      editor_(editor) {
  addButton(t_OK, 1);
  addButton(t_CANCEL, 0);

  // Probably not needed in the general case but no harm...
  // (avoid return + escape keys getting processed by the buttons..)
  for (int i = getNumChildComponents(); --i >= 0;)
    getChildComponent(i)->setWantsKeyboardFocus(false);

  setWantsKeyboardFocus(true);
  grabKeyboardFocus();
}

}  // namespace command
}  // namespace rec

