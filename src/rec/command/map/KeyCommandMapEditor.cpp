#include "rec/command/map/KeyCommandMapEditor.h"

#include "rec/base/Trans.h"
#include "rec/command/map/Key.h"
#include "rec/command/map/CommandMapItemComponent.h"

TRAN(PRESS_A_KEY, "Please press a key combination now...");
TRAN(KEY, "Key");

namespace rec {
namespace command {

namespace {

class KeyCommandEntryWindow : public CommandEntryWindow {
 public:
  KeyCommandEntryWindow(KeyCommandMapEditorBase& owner_)
      : CommandEntryWindow(t_PRESS_A_KEY), owner(owner_) {
  }

  bool keyPressed(const KeyPress& key) {
    lastKey_ = key;
    setMessage(owner.getKeyMessage(toString(key)));
    return true;
  }

  KeyPress lastKey_;
  KeyCommandMapEditorBase& owner;
};

}  // namespace

template <>
const String KeyCommandMapEditorBase::name() { return t_KEY; }

template <>
const String KeyCommandMapEditorBase::getDescription(const string& key) {
  return keyPressFromString(key).getTextDescriptionWithIcons();
}

template <>
void KeyCommandMapEditorBase::removeKey(CommandID command, int keyNum) {
  mappings_->removeKeyPress(command, keyNum);
}

template <>
KeyCommandMapEditorBase::KeyArray KeyCommandMapEditorBase::getKeys(CommandID cmd) {
  const Array<KeyPress>& kp = mappings_->getKeyPressesAssignedToCommand(cmd);
  KeyArray keyArray;
  for (int i = 0; i < kp.size(); ++i)
    keyArray.add(toString(kp[i]));
  return keyArray;
}

template <>
bool KeyCommandMapEditorBase::isValid(const string& key) {
  return keyPressFromString(key).isValid();
}

template <>
CommandID KeyCommandMapEditorBase::getCommand(const string& key) {
  return mappings_->findCommandForKeyPress(keyPressFromString(key));
}

template <>
void KeyCommandMapEditorBase::removeKey(const string& key) {
  mappings_->removeKeyPress(keyPressFromString(key));
}

template <>
void KeyCommandMapEditorBase::addKey(CommandID cmd, const string& key,
                                 int keyIndex) {
  mappings_->addKeyPress(cmd, keyPressFromString(key), keyIndex);
}

template <>
CommandEntryWindow* KeyCommandMapEditorBase::newWindow() {
  return new KeyCommandEntryWindow(*this);
}

template <>
void KeyCommandMapEditorBase::keyChosen(int result,
                                    CommandMapEditButton* button) {
  KeyCommandEntryWindow* window = dynamic_cast<KeyCommandEntryWindow*>(
      button->getCommandEntryWindow());
  if (result && button && window) {
    window->setVisible(false);
    window->owner.setNewKey(button, toString(window->lastKey_), false);
  }

  button->setCommandEntryWindow();
}

template <>
void KeyCommandMapEditorBase::assignNewKeyCallback(int result,
                                               CommandMapEditButton* button,
                                               const string* key) {
  if (result && button) {
    KeyCommandMapEditorBase* editor = dynamic_cast<KeyCommandMapEditorBase*>(
        &button->getOwner());
    editor->setNewKey(button, *key, true);
  }
}

}  // namespace command
}  // namespace rec
