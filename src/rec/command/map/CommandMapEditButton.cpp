#include "rec/command/map/CommandMapEditButton.h"
#include "rec/base/Trans.h"
#include "rec/command/map/CommandMapEditor.h"

namespace rec {
namespace command {

TRTR(ADD_NEW_KEY_MAPPING, "adds a new key-mapping");
TRTR(CHANGE_KEY_MAPPING, "click to change this key-mapping");
TRTR(CHANGE_COMMAND_MAPPING, "Change this command mapping");
TRTR(REMOVE_COMMAND_MAPPING, "Remove this command mapping");

CommandMapEditButton::CommandMapEditButton(CommandMapEditor& owner_,
                                           const CommandID commandID_,
                                           const String& keyName,
                                           const int keyNum_)
    : juce::Button (keyName),
      commandID (commandID_),
      keyNum (keyNum_),
      owner(owner_)
{
  setWantsKeyboardFocus (false);
  setTriggeredOnMouseDown (keyNum >= 0);

  setTooltip(keyNum_ < 0 ? ADD_NEW_KEY_MAPPING : CHANGE_KEY_MAPPING);
}

void CommandMapEditButton::paintButton (Graphics& g, bool /*isOver*/, bool /*isDown*/)
{
  getLookAndFeel().drawKeymapChangeButton (g, getWidth(), getHeight(), *this,
                                           keyNum >= 0 ? getName() : String::empty);
}

void CommandMapEditButton::addCommand() { owner.addButton(this); }
void CommandMapEditButton::removeCommand() { owner.removeButton(this); }


void CommandMapEditButton::menuCallback (int result, CommandMapEditButton* button)
{
  if (button != nullptr)
    {
      switch (result)
        {
       case 1: button->addCommand(); break;
       case 2: button->removeCommand(); break;
       default: break;
        }
    }
}

void CommandMapEditButton::clicked()
{
    if (keyNum >= 0)
    {
        // existing key clicked..
        PopupMenu m;
        m.addItem (1, CHANGE_COMMAND_MAPPING);
        m.addSeparator();
        m.addItem (2, REMOVE_COMMAND_MAPPING);

        m.showMenuAsync (PopupMenu::Options(),
                         ModalCallbackFunction::forComponent (menuCallback, this));
    }
    else
    {
        addCommand();  // + button pressed..
    }
}

void CommandMapEditButton::fitToContent (const int h) noexcept
{
    if (keyNum < 0)
    {
        setSize (h, h);
    }
    else
    {
        Font f (h * 0.6f);
        setSize (jlimit (h * 4, h * 8, 6 + f.getStringWidth (getName())), h);
    }
}

void CommandMapEditButton::registerAllTranslations() {
  ADD_NEW_KEY_MAPPING.translate();
  CHANGE_KEY_MAPPING.translate();
  CHANGE_COMMAND_MAPPING.translate();
  REMOVE_COMMAND_MAPPING.translate();
}

}  // namespace command
}  // namespace rec

