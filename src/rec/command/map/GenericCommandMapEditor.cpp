#include "rec/command/map/GenericCommandMapEditor.h"
#include "rec/base/Trans.h"

TRAN(CHANGE_KEY_MAPPING, "Change key-mapping");
TRAN(THIS_KEY_ASSIGNED, "This key is already assigned to the command");
TRAN(WANT_TO_REASSIGN, "Do you want to re-assign it to this new command instead?");
TRAN(REASSIGN, "Re-assign");
TRAN(CANCEL, "Cancel");
TRAN(CURRENTLY_ASSIGNED, "Currently assigned to");

namespace rec {
namespace command {

bool showCommandMapBox(const String& command, Component* comp,
                       ModalComponentManager::Callback* cb) {
  return AlertWindow::showOkCancelBox(
      AlertWindow::WarningIcon,
      t_CHANGE_KEY_MAPPING,
      str(t_THIS_KEY_ASSIGNED + " \"" + command +
          "\"\n\n" + t_WANT_TO_REASSIGN),
      t_REASSIGN, t_CANCEL, comp, cb);
}

String currentlyAssignedTo(const String& commandName) {
  return str("\n\n(" + t_CURRENTLY_ASSIGNED + " \"" + commandName + "\")");
}

}  // namespace command
}  // namespace rec
