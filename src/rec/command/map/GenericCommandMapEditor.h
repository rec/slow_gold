#ifndef __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
#define __REC_COMMAND_GENERICCOMMANDMAPEDITOR__

#include "rec/command/map/CommandMapEditor.h"
#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapEditorMappingItem.h"

namespace rec {
namespace command {

bool showCommandMapBox(const String& command,
                       Component* associatedComponent,
                       ModalComponentManager::Callback* callback);

String currentlyAssignedTo(const String& commandName);

template <typename MappingSet, typename Key>
class GenericCommandMapEditor : public CommandMapEditor {
 public:
  GenericCommandMapEditor(ApplicationCommandManager&, MappingSet&);
  MappingSet& getMappings() { return mappings_; }

  // You must implement these separately for any actual instantiation of this class.
  static const String getDescription(const Key&);
  static bool isValid(const Key&);
  static const String name();
  static void assignNewKeyCallback(int result, CommandMapEditButton*, Key);
  static void keyChosen(int result, CommandMapEditButton*);

  CommandID getCommand(const Key&);
  void removeKey(const Key&);
  void addKey(CommandID, const Key&, int keyIndex);
  void removeKey(CommandID, int keyNum);
  const Array<Key> getKeys(CommandID);
  CommandEntryWindow* newWindow();

  const String getKeyMessage(const Key& key);
  void setNewKey(CommandMapEditButton*, const Key&, bool dontAskUser);
  virtual const String getDescriptionForKey(const Key& key) const;
  virtual void addButton(CommandMapEditButton* b);
  virtual void removeButton(CommandMapEditButton* button);
  virtual void addChildren(CommandMapItemComponent* comp);

  static const int MAX_NUM_ASSIGNMENTS = 3;

 private:
  MappingSet& mappings_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(GenericCommandMapEditor);
};


template <typename MappingSet, typename Key>
void GenericCommandMapEditor<MappingSet, Key>::
setNewKey(CommandMapEditButton* button, const Key& newKey,
               bool dontAskUser) {
  if (isValid(newKey)) {
    const CommandID previousCommand = getCommand(newKey);

    if (previousCommand == 0 || dontAskUser) {
      removeKey(newKey);

      if (button->keyNum >= 0)
        removeKey(button->commandID, button->keyNum);

      addKey(button->commandID, newKey, button->keyNum);
    } else {
      showCommandMapBox(commandManager_.getNameOfCommand(previousCommand),
                        this,
                        ModalCallbackFunction::forComponent(
                            GenericCommandMapEditor<MappingSet,
                            Key>::assignNewKeyCallback,
                            button,
                            Key(newKey)));
    }
  }
}

template <typename MappingSet, typename Key>
GenericCommandMapEditor<MappingSet, Key>::
GenericCommandMapEditor(ApplicationCommandManager& manager, MappingSet& m)
    : CommandMapEditor(manager, m), mappings_(m) {
}


template <typename MappingSet, typename Key>
const String GenericCommandMapEditor<MappingSet, Key>::
getDescriptionForKey(const Key& key) const {
  return getDescription(key);
}

template <typename MappingSet, typename Key>
void GenericCommandMapEditor<MappingSet, Key>::
addButton(CommandMapEditButton* b) {
  CommandEntryWindow* w = newWindow();
  b->setCommandEntryWindow(w);
  w->enterModalState(true, ModalCallbackFunction::forComponent(keyChosen, b));
}

template <typename MappingSet, typename Key>
void GenericCommandMapEditor<MappingSet, Key>::
removeButton(CommandMapEditButton* button) {
  removeKey(button->commandID, button->keyNum);
}

template <typename MappingSet, typename Key>
void GenericCommandMapEditor<MappingSet, Key>::
addChildren(CommandMapItemComponent* comp) {
  CommandID command = comp->commandID_;
  const bool isReadOnly = isCommandReadOnly(command);
  const Array<Key> keys(getKeys(command));
  for (int i = 0; i < jmin(MAX_NUM_ASSIGNMENTS, keys.size()); ++i)
    comp->addButton(getDescriptionForKey(keys.getReference(i)), i, isReadOnly);
  comp->addButton(String::empty, -1, isReadOnly);
}

template <typename MappingSet, typename Key>
const String GenericCommandMapEditor<MappingSet, Key>::
getKeyMessage(const Key& key) {
  String message(name() + ": " + getDescription(key));
  const CommandID previousCommand = getCommand(key);
  if (previousCommand) {
    String pn = getCommandManager().getNameOfCommand(previousCommand);
    message += currentlyAssignedTo(pn);
  }

  return message;
}

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
