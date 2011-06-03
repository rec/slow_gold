#ifndef __REC_COMMAND_COMMANDMAPITEMCOMPONENT__
#define __REC_COMMAND_COMMANDMAPITEMCOMPONENT__

#include "rec/base/base.h"

namespace rec {
namespace command {

class CommandMapItemComponent  : public Component
{
public:
    CommandMapItemComponent(ApplicationCommandManager& manager_, const CommandID commandID_)
        : commandManager(manager_), commandID (commandID_)
    {
        setInterceptsMouseClicks (false, true);

        #if 0
        const bool isReadOnly = owner.isCommandReadOnly (commandID);

        const Array <KeyPress> keyPresses (owner.getMappings().getKeyPressesAssignedToCommand (commandID));
        for (int i = 0; i < jmin ((int) maxNumAssignments, keyPresses.size()); ++i)
            addKeyPressButton (owner.getDescriptionForKeyPress (keyPresses.getReference (i)), i, isReadOnly);
        addKeyPressButton (String::empty, -1, isReadOnly);
        #endif

    }

    void addKeyPressButton (const String& desc, const int index, const bool isReadOnly)
    {
        CommandMapEditButton* const b = makeButton(desc, index);
        buttons.add (b);

        b->setEnabled (! isReadOnly);
        b->setVisible (buttons.size() <= (int) maxNumAssignments);
        addChildComponent (b);
    }
    
    virtual CommandMapEditButton* makeButton(const String& desc, const int index) = 0;
    // new CommandMapEditButton(commandID, desc, index)

    void paint (Graphics& g)
    {
        g.setFont (getHeight() * 0.7f);
        g.setColour (findColour (CommandMapEditor::textColourId));

        g.drawFittedText (commandManager.getNameOfCommand (commandID),
                          4, 0, jmax (40, getChildComponent (0)->getX() - 5), getHeight(),
                          Justification::centredLeft, true);
    }

    void resized()
    {
        int x = getWidth() - 4;

        for (int i = buttons.size(); --i >= 0;)
        {
            CommandMapEditButton* const b = buttons.getUnchecked(i);

            b->fitToContent (getHeight() - 2);
            b->setTopRightPosition (x, 1);
            x = b->getX() - 5;
        }
    }

private:
    ApplicationCommandManager& commandManager;
    OwnedArray<CommandMapEditButton> buttons;
    const CommandID commandID;

    enum { maxNumAssignments = 3 };

    // Juce_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CommandMapItemComponent);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPITEMCOMPONENT__
