#include "rec/command/map/EditButton.h"
#include "rec/base/Trans.h"
#include "rec/command/map/Editor.h"

TRAN(ADD_NEW_KEY_MAPPING, "adds a new key-mapping");
TRAN(CHANGE_KEY_MAPPING, "click to change this key-mapping");
TRAN(CHANGE_COMMAND_MAPPING, "Change this command mapping");
TRAN(REMOVE_COMMAND_MAPPING, "Remove this command mapping");

namespace rec {
namespace command {

EditButton::EditButton(Editor& owner_,
                                           const CommandID commandID_,
                                           const String& keyName,
                                           const int keyNum_)
    : juce::Button(keyName),
      commandID(commandID_),
      keyNum(keyNum_),
      owner(owner_)
{
  setWantsKeyboardFocus(false);
  setTriggeredOnMouseDown(keyNum >= 0);

  setTooltip(keyNum_ < 0 ? t_ADD_NEW_KEY_MAPPING : t_CHANGE_KEY_MAPPING);
}

void EditButton::paintButton(Graphics& g, bool, bool) {
  getLookAndFeel().drawKeymapChangeButton(g, getWidth(), getHeight(),
                                          *this,
                                          (keyNum >= 0) ? getName() :
                                          String::empty);
}

void EditButton::menuCallback(int result,
                                        EditButton* button) {
  button->getOwner()->buttonMenuCallback(result, this);
}

void EditButton::clicked() {
  if (keyNum >= 0) {
    // existing key clicked..
    PopupMenu m;
    m.addItem(1, t_CHANGE_COMMAND_MAPPING);
    m.addSeparator();
    m.addItem(2, t_REMOVE_COMMAND_MAPPING);

    m.showMenuAsync(PopupMenu::Options(),
                    ModalCallbackFunction::forComponent(menuCallback, this));
  } else {
    addCommand();  // + button pressed..
  }
}

void EditButton::fitToContent(const int h) noexcept {
  if (keyNum < 0) {
    setSize(h, h);
  } else {
    Font f(h * 0.6f);
    setSize(jlimit(h * 4, h * 8, 6 + f.getStringWidth(getName())), h);
  }
}

}  // namespace command
}  // namespace rec

