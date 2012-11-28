#include "rec/command/map/KeyCommandMapEditor.h"
#include "rec/command/map/CommandMapItemComponent.h"
#include "rec/base/Trans.h"

TRAN(PRESS_A_KEY, "Please press a key combination now...");
TRAN(KEY, "Key");

namespace rec {
namespace command {

namespace {

class KeyCommandEntryWindow : public CommandEntryWindow {
 public:
  KeyCommandEntryWindow(KeyCommandMapEditor& owner_)
      : CommandEntryWindow(t_PRESS_A_KEY), owner(owner_) {
  }

  bool keyPressed(const KeyPress& key) {
    lastKey_ = key;
    setMessage(owner.getKeyMessage(key));
    return true;
  }

  KeyPress lastKey_;
  KeyCommandMapEditor& owner;
};

}  // namespace

template <>
const String KeyCommandMapEditor::name() { return t_KEY; }

template <>
const String KeyCommandMapEditor::getDescription(const KeyPress& key) {
  return key.getTextDescriptionWithIcons();
}

template <>
void KeyCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings_.removeKeyPress(command, keyNum);
}

template <>
KeyCommandMapEditor::KeyArray* KeyCommandMapEditor::getKeys(CommandID cmd) {
  const Array<KeyPress>& kp = mappings_.getKeyPressesAssignedToCommand(cmd);
  ptr<KeyArray> keyArray(new KeyArray);
  for (int i = 0; i < kp.size(); ++i)
    keyArray->add(new KeyPress(kp[i]));
  return keyArray.transfer();
}

template <>
bool KeyCommandMapEditor::isValid(const KeyPress& key) {
  return key.isValid();
}

template <>
CommandID KeyCommandMapEditor::getCommand(const KeyPress& key) {
  return mappings_.findCommandForKeyPress (key);
}

template <>
void KeyCommandMapEditor::removeKey(const KeyPress& key) {
  mappings_.removeKeyPress (key);
}

template <>
void KeyCommandMapEditor::addKey(CommandID cmd, const KeyPress& key,
                                 int keyIndex) {
  mappings_.addKeyPress(cmd, key, keyIndex);
}

template <>
CommandEntryWindow* KeyCommandMapEditor::newWindow() {
  return new KeyCommandEntryWindow(*this);
}

template <>
void KeyCommandMapEditor::keyChosen(int result,
                                    CommandMapEditButton* button) {
  KeyCommandEntryWindow* window = dynamic_cast<KeyCommandEntryWindow*>(
      button->getCommandEntryWindow());
  if (result != 0 && button != nullptr && window != nullptr) {
    window->setVisible (false);
    window->owner.setNewKey (button, window->lastKey_, false);
  }

  button->setCommandEntryWindow();
}

template <>
void KeyCommandMapEditor::assignNewKeyCallback(int result,
                                               CommandMapEditButton* button,
                                               const KeyPress* key) {
  if (result != 0 && button != nullptr) {
    KeyCommandMapEditor* editor = dynamic_cast<KeyCommandMapEditor*>(
        &button->getOwner());
    editor->setNewKey(button, *key, true);
  }
}

}  // namespace command
}  // namespace rec
