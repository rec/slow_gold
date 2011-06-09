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
  static void getDescription(const Key&);   // return key.getTextDescription();
  static void keyChosen(int result, CommandMapEditButton*);
  static void removeKey(MappingSet&, CommandID, int keyNum);
  static ApplicationCommandManager& getCommandManager(MappingSet&);
  static const Array <Key> getKeys(MappingSet&, CommandID);
  // getMappings().getKeyPressesAssignedToCommand(comp->commandID));

  //   return *mappingSet.getCommandManager();

  GenericCommandMapEditor(MappingSet& m) 
    : CommandMapEditor(getCommandManager(m), m), mappings(m) {
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
    removeKey(getMappings(), button->commandID, button->keyNum);
  }

  // void setNewKey (CommandMapEditButton* button, const Key& newKey, bool dontAskUser);
  virtual void addChildren(CommandMapItemComponent* comp) {
    const bool isReadOnly = isCommandReadOnly(comp->commandID);
    const Array<Key> keys(getKeys(getMappings()));
    for (int i = 0; i < jmin ((int) MAX_NUM_ASSIGNMENTS, keys.size()); ++i)
      comp->addButton (getDescriptionForKey (keys.getReference (i)), i, isReadOnly);
    comp->addButton (String::empty, -1, isReadOnly);
  }

  static const int MAX_NUM_ASSIGNMENTS = 3;

 private:
  KeyPressMappingSet& mappings;
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_GENERICCOMMANDMAPEDITOR__
