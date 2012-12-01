#ifndef __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
#define __REC_COMMAND_GENERICCOMMANDMAPEDITOR__

#include "rec/command/map/CommandMapEditor.h"
#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapEditorMappingItem.h"
#include "rec/command/map/Key.h"

namespace rec {
namespace command {

bool showCommandMapBox(const String& command,
                       Component* associatedComponent,
                       ModalComponentManager::Callback* callback);

String currentlyAssignedTo(const String& commandName);

template <typename MappingSet>
class GenericCommandMapEditor : public CommandMapEditor {
 public:
  GenericCommandMapEditor(ApplicationCommandManager*, MappingSet*);

  // You must implement these separately for any actual instantiation of this class.
  static void assignNewKeyCallback(int result, CommandMapEditButton*, const string*);
  static void keyChosen(int result, CommandMapEditButton*);

  void setNewKey(CommandMapEditButton*, const string&, bool dontAskUser);
  virtual void addButton(CommandMapEditButton* b);

 protected:
  MappingSet* mappings_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GenericCommandMapEditor);
};

template <typename MappingSet>
void GenericCommandMapEditor<MappingSet>::
setNewKey(CommandMapEditButton* button, const string& newKey, bool dontAskUser) {
  DLOG(INFO) << "adding new key";
  if (isValid(newKey)) {
    const CommandID previousCommand = getCommand(newKey);
    if (previousCommand == 0 || dontAskUser) {
      removeKey(newKey);
      if (button->keyNum >= 0)
        removeKey(button->commandID, button->keyNum);
      addKey(button->commandID, newKey, button->keyNum);
    } else {
      showCommandMapBox(commandManager_->getNameOfCommand(previousCommand),
                        this,
                        ModalCallbackFunction::forComponent(
                            GenericCommandMapEditor<MappingSet>::
                            assignNewKeyCallback,
                            button, &newKey));
    }
  }
}

template <typename MappingSet>
GenericCommandMapEditor<MappingSet>::
GenericCommandMapEditor(ApplicationCommandManager* manager, MappingSet* m)
    : CommandMapEditor(manager, m), mappings_(m) {
}

template <typename MappingSet>
void GenericCommandMapEditor<MappingSet>::
addButton(CommandMapEditButton* b) {
  CommandEntryWindow* w = newWindow();
  b->setCommandEntryWindow(w);
  w->enterModalState(true, ModalCallbackFunction::forComponent(keyChosen, b));
}

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
