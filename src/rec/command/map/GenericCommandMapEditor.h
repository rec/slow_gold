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
  static const String getDescription(const string&);
  static bool isValid(const string&);
  static const String name();
  static void assignNewKeyCallback(int result, CommandMapEditButton*, const string*);
  static void keyChosen(int result, CommandMapEditButton*);

  CommandID getCommand(const string&);
  void removeKey(const string&);
  void addKey(CommandID, const string&, int keyIndex);
  void removeKey(CommandID, int keyNum);

  typedef juce::Array<string> KeyArray;
  KeyArray getKeys(CommandID);
  CommandEntryWindow* newWindow();

  const String getKeyMessage(const string& key);
  void setNewKey(CommandMapEditButton*, const string&, bool dontAskUser);
  virtual const String getDescriptionForKey(const string& key) const;
  virtual void addButton(CommandMapEditButton* b);
  virtual void removeButton(CommandMapEditButton* button);
  virtual void addChildren(CommandMapItemComponent* comp);

  static const int MAX_NUM_ASSIGNMENTS = 3;

 private:
  MappingSet* mappings_;

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
const String GenericCommandMapEditor<MappingSet>::
getDescriptionForKey(const string& key) const {
  return getDescription(key);
}

template <typename MappingSet>
void GenericCommandMapEditor<MappingSet>::
addButton(CommandMapEditButton* b) {
  CommandEntryWindow* w = newWindow();
  b->setCommandEntryWindow(w);
  w->enterModalState(true, ModalCallbackFunction::forComponent(keyChosen, b));
}

template <typename MappingSet>
void GenericCommandMapEditor<MappingSet>::
removeButton(CommandMapEditButton* button) {
  removeKey(button->commandID, button->keyNum);
}

template <typename MappingSet>
void GenericCommandMapEditor<MappingSet>::
addChildren(CommandMapItemComponent* comp) {
  CommandID command = comp->commandID_;
  const bool isReadOnly = isCommandReadOnly(command);
  KeyArray keys = getKeys(command);
  for (int i = 0; i < jmin(MAX_NUM_ASSIGNMENTS, keys.size()); ++i)
    comp->addButton(getDescriptionForKey(keys[i]), i, isReadOnly);
  comp->addButton(String::empty, -1, isReadOnly);
}

template <typename MappingSet>
const String GenericCommandMapEditor<MappingSet>::
getKeyMessage(const string& key) {
  String message(name() + ": " + getDescription(key));
  const CommandID previousCommand = getCommand(key);
  if (previousCommand) {
    String pn = getCommandManager()->getNameOfCommand(previousCommand);
    message += currentlyAssignedTo(pn);
  }

  return message;
}

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
