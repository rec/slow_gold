#ifndef __REC_COMMAND_COMMANDMAPEDITBUTTON__
#define __REC_COMMAND_COMMANDMAPEDITBUTTON__

#include "rec/command/CommandEntryWindow.h"

namespace rec {
namespace command {

class CommandMapEditButton  : public Button
{
public:
    CommandMapEditButton(const CommandID commandID_,
               const String& keyName,
               const int keyNum_)
        : Button (keyName),
          commandID (commandID_),
          keyNum (keyNum_)
    {
        setWantsKeyboardFocus (false);
        setTriggeredOnMouseDown (keyNum >= 0);

        setTooltip (keyNum_ < 0 ? TRANS("adds a new key-mapping")
                                : TRANS("click to change this key-mapping"));
    }

    void paintButton (Graphics& g, bool /*isOver*/, bool /*isDown*/)
    {
        getLookAndFeel().drawKeymapChangeButton (g, getWidth(), getHeight(), *this,
                                                 keyNum >= 0 ? getName() : String::empty);
    }

    static void menuCallback (int result, CommandMapEditButton* button)
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

    virtual void addCommand() = 0;
    virtual void removeCommand() = 0;
    // case 1: button->assignNewKey(); break;
    // case 2: button->owner.getMappings().removeKeyPress (button->commandID, button->keyNum); break;

    void clicked()
    {
        if (keyNum >= 0)
        {
            // existing key clicked..
            PopupMenu m;
            m.addItem (1, TRANS("Change this command mapping"));
            m.addSeparator();
            m.addItem (2, TRANS("Remove this command mapping"));

            m.showMenuAsync (PopupMenu::Options(),
                             ModalCallbackFunction::forComponent (menuCallback, this));
        }
        else
        {
            addCommand();  // + button pressed..
        }
    }

    void fitToContent (const int h) noexcept
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


private:
    const CommandID commandID;
    const int keyNum;
    ScopedPointer<CommandEntryWindow> currentCommandEntryWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CommandMapEditButton);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITBUTTON__
