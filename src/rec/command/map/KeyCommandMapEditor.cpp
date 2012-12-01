#include "rec/command/map/KeyCommandMapEditor.h"

#include "rec/base/Trans.h"
#include "rec/command/map/Key.h"
#include "rec/command/map/CommandEntryWindow.h"
#include "rec/command/map/CommandMapItemComponent.h"

TRAN(PRESS_A_KEY, "Please press a key combination now...");
TRAN(KEY, "Key");

namespace rec {
namespace command {

namespace {

class KeyCommandEntryWindow : public CommandEntryWindow {
 public:
  explicit KeyCommandEntryWindow(KeyCommandMapEditor* owner)
    : CommandEntryWindow(t_PRESS_A_KEY, owner) {
  }

  bool keyPressed(const KeyPress& key) {
    setLastKey(toString(key));
    return true;
  }

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(KeyCommandEntryWindow);
};

}  // namespace

const String KeyCommandMapEditor::name() const {
  return t_KEY;
}

bool KeyCommandMapEditor::isValid(const string& key) const {
  return keyPressFromString(key).isValid();
}

const String KeyCommandMapEditor::getDescription(const string& key) const {
  return keyPressFromString(key).getTextDescriptionWithIcons();
}

CommandID KeyCommandMapEditor::getCommand(const string& key) {
  return mappings_->findCommandForKeyPress(keyPressFromString(key));
}

void KeyCommandMapEditor::removeKey(const string& key) {
  mappings_->removeKeyPress(keyPressFromString(key));
}

void KeyCommandMapEditor::addKey(CommandID cmd, const string& key, int index) {
  mappings_->addKeyPress(cmd, keyPressFromString(key), index);
}

void KeyCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings_->removeKeyPress(command, keyNum);
}

CommandMapEditor::KeyArray KeyCommandMapEditor::getKeys(CommandID cmd) {
  const Array<KeyPress>& kp = mappings_->getKeyPressesAssignedToCommand(cmd);
  KeyArray keyArray;
  for (int i = 0; i < kp.size(); ++i)
    keyArray.add(toString(kp[i]));
  return keyArray;
}

CommandEntryWindow* KeyCommandMapEditor::newWindow() {
  return new KeyCommandEntryWindow(this);
}

}  // namespace command
}  // namespace rec
