#include "rec/command/KeyCommandMapEditor.h"
#include "rec/command/CommandMapItemComponent.h"

namespace rec {
namespace command {

namespace {

class KeyCommandEntryWindow : public CommandEntryWindow {
 public:
    KeyCommandEntryWindow(GenericCommandMapEditor<KeyPressMappingSet, KeyPress>& owner_)
        : CommandEntryWindow("Please press a key combination now..."), owner(owner_)
    {
    }

    bool keyPressed (const KeyPress& key)
    {
        lastPress = key;
        String message (TRANS("Key: ") + owner.getDescriptionForKey (key));

        const CommandID previousCommand = owner.getMappings().findCommandForKeyPress (key);

        if (previousCommand != 0)
            message << "\n\n" << TRANS("(Currently assigned to \"")
                    << owner.getCommandManager().getNameOfCommand (previousCommand) << "\")";

        setMessage (message);
        return true;
    }

    bool keyStateChanged (bool)
    {
        return true;
    }

    KeyPress lastPress;
    GenericCommandMapEditor<KeyPressMappingSet, KeyPress>& owner;
};

}  // namespace

template <>
const String GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::getDescription(const KeyPress& key) {
  return key.getTextDescription();
}

template <>
void GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::removeKey(CommandID command, int keyNum) {
  mappings.removeKeyPress(command, keyNum);
}

template <>
ApplicationCommandManager& GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::commandManager(KeyPressMappingSet& mappings) {
  return *mappings.getCommandManager();
}

template <>
const Array<KeyPress> GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::getKeys(CommandID cmd) {
  return mappings.getKeyPressesAssignedToCommand(cmd);
}

template <>
bool GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::isValid(const KeyPress& key) {
  return key.isValid();
}

template <>
CommandID GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::getCommand(const KeyPress& key) {
  return mappings.findCommandForKeyPress (key);
}

template <>
void GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::removeKey(const KeyPress& key) {
  mappings.removeKeyPress (key);
}

template <>
void GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::addKey(CommandID cmd, const KeyPress& key, int keyIndex) {
  mappings.addKeyPress(cmd, key, keyIndex);
}

template <>
CommandEntryWindow* GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::newWindow() {
  return new KeyCommandEntryWindow(*this);
}

template <>
void GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::keyChosen (int result, CommandMapEditButton* button)
{
    KeyCommandEntryWindow* window = dynamic_cast<KeyCommandEntryWindow*>(button->getCommandEntryWindow());
    if (result != 0 && button != nullptr && window != nullptr)
    {
        window->setVisible (false);
        window->owner.setNewKey (button, window->lastPress, false);
    }

    button->setCommandEntryWindow();
}

template <>
void GenericCommandMapEditor<KeyPressMappingSet, KeyPress>::assignNewKeyCallback(int result, CommandMapEditButton* button, KeyPress key) {
     if (result != 0 && button != nullptr) {
         GenericCommandMapEditor<KeyPressMappingSet, KeyPress>* editor = dynamic_cast<GenericCommandMapEditor<KeyPressMappingSet, KeyPress>*>(&button->getOwner());
         editor->setNewKey (button, key, true);
     }
}

}  // namespace command
}  // namespace rec
