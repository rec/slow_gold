#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapEditor.h"

namespace rec {
namespace command {

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

  setTooltip (keyNum_ < 0 ? trans("adds a new key-mapping")
              : trans("click to change this key-mapping"));
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
        m.addItem (1, trans("Change this command mapping"));
        m.addSeparator();
        m.addItem (2, trans("Remove this command mapping"));

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


}  // namespace command
}  // namespace rec

