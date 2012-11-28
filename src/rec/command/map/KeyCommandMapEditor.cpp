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
    setMessage(owner.getKeyMessage(Key<KeyPress>(key)));
    return true;
  }

  KeyPress lastKey_;
  KeyCommandMapEditor& owner;
};

const KeyPress* cast(const KeyBase& key) {
  if (const Key<KeyPress>* kp = dynamic_cast<const Key<KeyPress>*>(&key))
    return &(kp->key());
  LOG(DFATAL) << "Couldn't understand key";
  return NULL;
}

}  // namespace

template <>
const String KeyCommandMapEditor::name() { return t_KEY; }

template <>
const String KeyCommandMapEditor::getDescription(const KeyBase& key) {
  String result;
  if (const KeyPress* k = cast(key))
    result = k->getTextDescriptionWithIcons();

  return result;
}

template <>
void KeyCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings_->removeKeyPress(command, keyNum);
}

template <>
KeyCommandMapEditor::KeyArray* KeyCommandMapEditor::getKeys(CommandID cmd) {
  const Array<KeyPress>& kp = mappings_->getKeyPressesAssignedToCommand(cmd);
  ptr<KeyArray> keyArray(new KeyArray);
  for (int i = 0; i < kp.size(); ++i)
    keyArray->add(new Key<KeyPress>(KeyPress(kp[i])));
  return keyArray.transfer();
}

template <>
bool KeyCommandMapEditor::isValid(const KeyBase& key) {
  const KeyPress* k = cast(key);
  return k && k->isValid();
}

template <>
CommandID KeyCommandMapEditor::getCommand(const KeyBase& key) {
  if (const KeyPress* k = cast(key))
    return mappings_->findCommandForKeyPress(*k);
  else
    return 0;
}

template <>
void KeyCommandMapEditor::removeKey(const KeyBase& key) {
  if (const KeyPress* k = cast(key))
    mappings_->removeKeyPress(*k);
}

template <>
void KeyCommandMapEditor::addKey(CommandID cmd, const KeyBase& key,
                                 int keyIndex) {
  if (const KeyPress* k = cast(key))
    mappings_->addKeyPress(cmd, *k, keyIndex);
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
    window->owner.setNewKey (button, Key<KeyPress>(window->lastKey_), false);
  }

  button->setCommandEntryWindow();
}

template <>
void KeyCommandMapEditor::assignNewKeyCallback(int result,
                                               CommandMapEditButton* button,
                                               const KeyBase* key) {
  if (result && button) {
    KeyCommandMapEditor* editor = dynamic_cast<KeyCommandMapEditor*>(
        &button->getOwner());
    editor->setNewKey(button, *key, true);
  }
}

}  // namespace command
}  // namespace rec
