#include "rec/command/map/GenericCommandMapEditor.h"
#include "rec/base/Trans.h"

namespace rec {
namespace command {

namespace {

Trans CHANGE_KEY_MAPPING("Change key-mapping");
Trans THIS_KEY_ASSIGNED("This key is already assigned to the command");
Trans WANT_TO_REASSIGN("Do you want to re-assign it to this new command instead?");
Trans REASSIGN("Re-assign");
Trans CANCEL("Cancel");
Trans CURRENTLY_ASSIGNED("Currently assigned to");

}  // namespace;

bool showCommandMapBox(const String& command, Component* comp,
                       ModalComponentManager::Callback* cb) {
  return AlertWindow::showOkCancelBox(
      AlertWindow::WarningIcon,
      CHANGE_KEY_MAPPING,
      str(THIS_KEY_ASSIGNED + " \"" + command + "\"\n\n" + WANT_TO_REASSIGN),
      REASSIGN, CANCEL, comp, cb);
}

String currentlyAssignedTo(const String& commandName) {
  return str("\n\n(" + CURRENTLY_ASSIGNED + " \"" + commandName + "\")");
}

void CommandMapEditorTranslation::translateAll() {
  CHANGE_KEY_MAPPING.translate();
  THIS_KEY_ASSIGNED.translate();
  WANT_TO_REASSIGN.translate();
  REASSIGN.translate();
  CANCEL.translate();
  CURRENTLY_ASSIGNED.translate();
}

}  // namespace command
}  // namespace rec
