#include "rec/command/map/KeyStrokeEditor.h"

#include "rec/base/Trans.h"
#include "rec/command/map/Items.h"

TRAN(PRESS_A_KEY, "Please press a key combination now...");
TRAN(KEY, "Key");

namespace rec {
namespace command {

const String KeyStrokeEditor::name() const {
  return t_KEY;
}

const String KeyStrokeEditor::getWindowTitle() const {
  return t_PRESS_A_KEY;
}

bool KeyStrokeEditor::isValid(const string& key) const {
  return keyPressFromString(key).isValid();
}

const String KeyStrokeEditor::getDescription(const string& key) const {
  return keyPressFromString(key).getTextDescriptionWithIcons();
}

juce::AlertWindow* KeyStrokeEditor::newWindow() {
  ptr<juce::AlertWindow> window(Editor::newWindow());
  window->addKeyListener(this);
  return window.transfer();
}

bool KeyStrokeEditor::keyPressed(const KeyPress& kp, Component*) {
  setKey(toString(kp));
  return true;
}

}  // namespace command
}  // namespace rec
