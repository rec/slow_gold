#include "rec/command/map/KeyStrokeEditor.h"

#include "rec/base/Trans.h"
#include "rec/command/map/Key.h"
#include "rec/command/map/EntryWindow.h"
#include "rec/command/map/MapItemComponent.h"

TRAN(PRESS_A_KEY, "Please press a key combination now...");
TRAN(KEY, "Key");

namespace rec {
namespace command {

namespace {

class KeyEntryWindow : public EntryWindow {
 public:
  explicit KeyEntryWindow(KeyStrokeEditor* owner)
    : EntryWindow(t_PRESS_A_KEY, owner) {
  }

  bool keyPressed(const KeyPress& key) {
    editor()->setKey(toString(key));
    return true;
  }

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(KeyEntryWindow);
};

}  // namespace

const String KeyStrokeEditor::name() const {
  return t_KEY;
}

const String KeyStrokeEditor::dialogTitle() const {
  return t_PRESS_A_KEY;
}

bool KeyStrokeEditor::isValid(const string& key) const {
  return keyPressFromString(key).isValid();
}

const String KeyStrokeEditor::getDescription(const string& key) const {
  return keyPressFromString(key).getTextDescriptionWithIcons();
}

EntryWindow* KeyStrokeEditor::newWindow() {
  ptr<EntryWindow> w(new EntryWindow(t_PRESS_A_KEY, this));
  w->addKeyListener(this);
}

bool KeyEntryWindow::keyPressed(const KeyPress& kp) {
  setKey(toString(kp));
}

}  // namespace command
}  // namespace rec
