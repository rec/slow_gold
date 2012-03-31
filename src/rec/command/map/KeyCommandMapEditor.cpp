#include "rec/command/map/KeyCommandMapEditor.h"
#include "rec/command/map/CommandMapItemComponent.h"

namespace rec {
namespace command {

// i18n

namespace {

class KeyCommandEntryWindow : public CommandEntryWindow {
 public:
    KeyCommandEntryWindow(KeyCommandMapEditor& owner_)
        : CommandEntryWindow("Please press a key combination now..."), owner(owner_)
    {
    }

    bool keyPressed (const KeyPress& key)
    {
        lastKey_ = key;
        setMessage(owner.getKeyMessage(key));
        return true;
    }
#if 0
    bool keyStateChanged (bool)
    {
        return true;
    }
#endif
    KeyPress lastKey_;
    KeyCommandMapEditor& owner;
};

}  // namespace

template <>
const String KeyCommandMapEditor::name() { return "Key"; }

template <>
const String KeyCommandMapEditor::getDescription(const KeyPress& key) {
  return key.getTextDescription();
}

template <>
void KeyCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings.removeKeyPress(command, keyNum);
}

template <>
const Array<KeyPress> KeyCommandMapEditor::getKeys(CommandID cmd) {
  return mappings.getKeyPressesAssignedToCommand(cmd);
}

template <>
bool KeyCommandMapEditor::isValid(const KeyPress& key) {
  return key.isValid();
}

template <>
CommandID KeyCommandMapEditor::getCommand(const KeyPress& key) {
  return mappings.findCommandForKeyPress (key);
}

template <>
void KeyCommandMapEditor::removeKey(const KeyPress& key) {
  mappings.removeKeyPress (key);
}

template <>
void KeyCommandMapEditor::addKey(CommandID cmd, const KeyPress& key, int keyIndex) {
  mappings.addKeyPress(cmd, key, keyIndex);
}

template <>
CommandEntryWindow* KeyCommandMapEditor::newWindow() {
  return new KeyCommandEntryWindow(*this);
}

template <>
void KeyCommandMapEditor::keyChosen (int result, CommandMapEditButton* button)
{
    KeyCommandEntryWindow* window = dynamic_cast<KeyCommandEntryWindow*>(button->getCommandEntryWindow());
    if (result != 0 && button != nullptr && window != nullptr)
    {
        window->setVisible (false);
        window->owner.setNewKey (button, window->lastKey_, false);
    }

    button->setCommandEntryWindow();
}

template <>
void KeyCommandMapEditor::assignNewKeyCallback(int result, CommandMapEditButton* button, KeyPress key) {
     if (result != 0 && button != nullptr) {
         KeyCommandMapEditor* editor = dynamic_cast<KeyCommandMapEditor*>(&button->getOwner());
         editor->setNewKey (button, key, true);
     }
}

}  // namespace command
}  // namespace rec
