#ifndef __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
#define __REC_COMMAND_GENERICCOMMANDMAPEDITOR__

#include "rec/command/CommandMapEditor.h"
#include "rec/command/CommandMapEditButton.h"
#include "rec/command/CommandMapEditorMappingItem.h"

namespace rec {
namespace command {

template <typename MappingSet, typename Key>
class GenericCommandMapEditor : public CommandMapEditor {
 public:
  // You must implement these separately for any actual instantiation of this class.
  static const String getDescription(const Key&);
  static void keyChosen(int result, CommandMapEditButton*);
  static void assignNewKeyCallback(int result, CommandMapEditButton*, Key);
  static bool isValid(const Key&);

  CommandID getCommand(const Key&);
  void removeKey(const Key&);
  void addKey(CommandID, const Key&, int keyIndex);
  void removeKey(CommandID, int keyNum);
  const Array <Key> getKeys(CommandID);
  CommandEntryWindow* newWindow();

  void setNewKey (CommandMapEditButton* button, const KeyPress& newKey, bool dontAskUser)
  {
      if (isValid(newKey))
      {
        const CommandID previousCommand = getCommand(newKey);

          if (previousCommand == 0 || dontAskUser)
          {
              removeKey (newKey);

              if (button->keyNum >= 0)
                removeKey (button->commandID, button->keyNum);

              addKey(button->commandID, newKey, button->keyNum);
          }
          else
          {
              AlertWindow::showOkCancelBox (AlertWindow::WarningIcon,
                                            TRANS("Change key-mapping"),
                                            TRANS("This key is already assigned to the command \"")
                                              + getMappings().getCommandManager()->getNameOfCommand (previousCommand)
                                              + TRANS("\"\n\nDo you want to re-assign it to this new command instead?"),
                                            TRANS("Re-assign"),
                                            TRANS("Cancel"),
                                            this,
                                            ModalCallbackFunction::forComponent (GenericCommandMapEditor<MappingSet, Key>::assignNewKeyCallback,
                                                                                 button, KeyPress (newKey)));
          }
      }
  }

  GenericCommandMapEditor(ApplicationCommandManager& manager, MappingSet& m)
    : CommandMapEditor(manager, m), mappings(m) {
  }

  MappingSet& getMappings() { return mappings; }

  virtual const String getDescriptionForKey(const Key& key) const {
    return getDescription(key);
  }

  virtual void addButton(CommandMapEditButton* b) {
    CommandEntryWindow* w = newWindow();
    b->setCommandEntryWindow(w);
    w->enterModalState (true, ModalCallbackFunction::forComponent(keyChosen, b));
  }

  virtual void removeButton(CommandMapEditButton* button) {
    removeKey(button->commandID, button->keyNum);
  }

  virtual void addChildren(CommandMapItemComponent* comp) {
    CommandID command = comp->commandID;
    const bool isReadOnly = isCommandReadOnly(command);
    const Array<Key> keys(getKeys(command));
    for (int i = 0; i < jmin ((int) MAX_NUM_ASSIGNMENTS, keys.size()); ++i)
      comp->addButton (getDescriptionForKey (keys.getReference (i)), i, isReadOnly);
    comp->addButton (String::empty, -1, isReadOnly);
  }

  static const int MAX_NUM_ASSIGNMENTS = 3;

 private:
  MappingSet& mappings;
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
