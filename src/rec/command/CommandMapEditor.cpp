#include "rec/command/CommandMapEditor.h"

namespace rec {
namespace command {

class CommandMapEditor::ChangeKeyButton  : public Button
{
public:
    ChangeKeyButton (CommandMapEditor& owner_,
                     const CommandID commandID_,
                     const String& keyName,
                     const int keyNum_)
        : Button (keyName),
          owner (owner_),
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

    static void menuCallback (int result, ChangeKeyButton* button)
    {
        if (button != nullptr)
        {
            switch (result)
            {
                case 1: button->assignNewKey(); break;
                case 2: button->owner.getMappings().removeKeyPress (button->commandID, button->keyNum); break;
                default: break;
            }
        }
    }

    void clicked()
    {
        if (keyNum >= 0)
        {
            // existing key clicked..
            PopupMenu m;
            m.addItem (1, TRANS("change this key-mapping"));
            m.addSeparator();
            m.addItem (2, TRANS("remove this key-mapping"));

            m.showMenuAsync (PopupMenu::Options(),
                             ModalCallbackFunction::forComponent (menuCallback, this));
        }
        else
        {
            assignNewKey();  // + button pressed..
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

    //==============================================================================
    class KeyEntryWindow  : public AlertWindow
    {
    public:
        KeyEntryWindow (CommandMapEditor& owner_)
            : AlertWindow (TRANS("New key-mapping"),
                           TRANS("Please press a key combination now..."),
                           AlertWindow::NoIcon),
              owner (owner_)
        {
            addButton (TRANS("Ok"), 1);
            addButton (TRANS("Cancel"), 0);

            // (avoid return + escape keys getting processed by the buttons..)
            for (int i = getNumChildComponents(); --i >= 0;)
                getChildComponent (i)->setWantsKeyboardFocus (false);

            setWantsKeyboardFocus (true);
            grabKeyboardFocus();
        }

        bool keyPressed (const KeyPress& key)
        {
            lastPress = key;
            String message (TRANS("Key: ") + owner.getDescriptionForKeyPress (key));

            const CommandID previousCommand = owner.getMappings().findCommandForKeyPress (key);

            if (previousCommand != 0)
                message << "\n\n" << TRANS("(Currently assigned to \"")
                        << owner.getMappings().getCommandManager()->getNameOfCommand (previousCommand) << "\")";

            setMessage (message);
            return true;
        }

        bool keyStateChanged (bool)
        {
            return true;
        }

        KeyPress lastPress;

    private:
        CommandMapEditor& owner;

        JUCE_DECLARE_NON_COPYABLE (KeyEntryWindow);
    };

    static void assignNewKeyCallback (int result, ChangeKeyButton* button, KeyPress newKey)
    {
        if (result != 0 && button != nullptr)
            button->setNewKey (newKey, true);
    }

    void setNewKey (const KeyPress& newKey, bool dontAskUser)
    {
        if (newKey.isValid())
        {
            const CommandID previousCommand = owner.getMappings().findCommandForKeyPress (newKey);

            if (previousCommand == 0 || dontAskUser)
            {
                owner.getMappings().removeKeyPress (newKey);

                if (keyNum >= 0)
                    owner.getMappings().removeKeyPress (commandID, keyNum);

                owner.getMappings().addKeyPress (commandID, newKey, keyNum);
            }
            else
            {
                AlertWindow::showOkCancelBox (AlertWindow::WarningIcon,
                                              TRANS("Change key-mapping"),
                                              TRANS("This key is already assigned to the command \"")
                                                + owner.getMappings().getCommandManager()->getNameOfCommand (previousCommand)
                                                + TRANS("\"\n\nDo you want to re-assign it to this new command instead?"),
                                              TRANS("Re-assign"),
                                              TRANS("Cancel"),
                                              this,
                                              ModalCallbackFunction::forComponent (assignNewKeyCallback,
                                                                                   this, KeyPress (newKey)));
            }
        }
    }

    static void keyChosen (int result, ChangeKeyButton* button)
    {
        if (result != 0 && button != nullptr && button->currentKeyEntryWindow != nullptr)
        {
            button->currentKeyEntryWindow->setVisible (false);
            button->setNewKey (button->currentKeyEntryWindow->lastPress, false);
        }

        button->currentKeyEntryWindow = nullptr;
    }

    void assignNewKey()
    {
        currentKeyEntryWindow = new KeyEntryWindow (owner);
        currentKeyEntryWindow->enterModalState (true, ModalCallbackFunction::forComponent (keyChosen, this));
    }

private:
    CommandMapEditor& owner;
    const CommandID commandID;
    const int keyNum;
    ScopedPointer<KeyEntryWindow> currentKeyEntryWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChangeKeyButton);
};

//==============================================================================
class CommandMapEditor::ItemComponent  : public Component
{
public:
    ItemComponent (CommandMapEditor& owner_, const CommandID commandID_)
        : owner (owner_), commandID (commandID_)
    {
        setInterceptsMouseClicks (false, true);

        const bool isReadOnly = owner.isCommandReadOnly (commandID);

        const Array <KeyPress> keyPresses (owner.getMappings().getKeyPressesAssignedToCommand (commandID));

        for (int i = 0; i < jmin ((int) maxNumAssignments, keyPresses.size()); ++i)
            addKeyPressButton (owner.getDescriptionForKeyPress (keyPresses.getReference (i)), i, isReadOnly);

        addKeyPressButton (String::empty, -1, isReadOnly);
    }

    void addKeyPressButton (const String& desc, const int index, const bool isReadOnly)
    {
        ChangeKeyButton* const b = new ChangeKeyButton (owner, commandID, desc, index);
        keyChangeButtons.add (b);

        b->setEnabled (! isReadOnly);
        b->setVisible (keyChangeButtons.size() <= (int) maxNumAssignments);
        addChildComponent (b);
    }

    void paint (Graphics& g)
    {
        g.setFont (getHeight() * 0.7f);
        g.setColour (findColour (CommandMapEditor::textColourId));

        g.drawFittedText (owner.getMappings().getCommandManager()->getNameOfCommand (commandID),
                          4, 0, jmax (40, getChildComponent (0)->getX() - 5), getHeight(),
                          Justification::centredLeft, true);
    }

    void resized()
    {
        int x = getWidth() - 4;

        for (int i = keyChangeButtons.size(); --i >= 0;)
        {
            ChangeKeyButton* const b = keyChangeButtons.getUnchecked(i);

            b->fitToContent (getHeight() - 2);
            b->setTopRightPosition (x, 1);
            x = b->getX() - 5;
        }
    }

private:
    CommandMapEditor& owner;
    OwnedArray<ChangeKeyButton> keyChangeButtons;
    const CommandID commandID;

    enum { maxNumAssignments = 3 };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ItemComponent);
};

//==============================================================================
class CommandMapEditor::MappingItem  : public TreeViewItem
{
public:
    MappingItem (CommandMapEditor& owner_, const CommandID commandID_)
        : owner (owner_), commandID (commandID_)
    {
    }

    const String getUniqueName() const          { return String ((int) commandID) + "_id"; }
    bool mightContainSubItems()                 { return false; }
    int getItemHeight() const                   { return 20; }

    Component* createItemComponent()
    {
        return new ItemComponent (owner, commandID);
    }

private:
    CommandMapEditor& owner;
    const CommandID commandID;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MappingItem);
};


//==============================================================================
class CommandMapEditor::CategoryItem  : public TreeViewItem
{
public:
    CategoryItem (CommandMapEditor& owner_, const String& name)
        : owner (owner_), categoryName (name)
    {
    }

    const String getUniqueName() const          { return categoryName + "_cat"; }
    bool mightContainSubItems()                 { return true; }
    int getItemHeight() const                   { return 28; }

    void paintItem (Graphics& g, int width, int height)
    {
        g.setFont (height * 0.6f, Font::bold);
        g.setColour (owner.findColour (CommandMapEditor::textColourId));

        g.drawText (categoryName,
                    2, 0, width - 2, height,
                    Justification::centredLeft, true);
    }

    void itemOpennessChanged (bool isNowOpen)
    {
        if (isNowOpen)
        {
            if (getNumSubItems() == 0)
            {
                Array <CommandID> commands (owner.getMappings().getCommandManager()->getCommandsInCategory (categoryName));

                for (int i = 0; i < commands.size(); ++i)
                {
                    if (owner.shouldCommandBeIncluded (commands[i]))
                        addSubItem (new MappingItem (owner, commands[i]));
                }
            }
        }
        else
        {
            clearSubItems();
        }
    }

private:
    CommandMapEditor& owner;
    String categoryName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CategoryItem);
};

//==============================================================================
class CommandMapEditor::TopLevelItem   : public TreeViewItem,
                                                  public ChangeListener,
                                                  public ButtonListener
{
public:
    TopLevelItem (CommandMapEditor& owner_)
        : owner (owner_)
    {
        setLinesDrawnForSubItems (false);
        owner.getMappings().addChangeListener (this);
    }

    ~TopLevelItem()
    {
        owner.getMappings().removeChangeListener (this);
    }

    bool mightContainSubItems()             { return true; }
    const String getUniqueName() const      { return "keys"; }

    void changeListenerCallback (ChangeBroadcaster*)
    {
        const OpennessRestorer openness (*this);
        clearSubItems();

        const StringArray categories (owner.getMappings().getCommandManager()->getCommandCategories());

        for (int i = 0; i < categories.size(); ++i)
        {
            const Array <CommandID> commands (owner.getMappings().getCommandManager()->getCommandsInCategory (categories[i]));
            int count = 0;

            for (int j = 0; j < commands.size(); ++j)
                if (owner.shouldCommandBeIncluded (commands[j]))
                    ++count;

            if (count > 0)
                addSubItem (new CategoryItem (owner, categories[i]));
        }
    }

    static void resetToDefaultsCallback (int result, CommandMapEditor* owner)
    {
        if (result != 0 && owner != nullptr)
            owner->getMappings().resetToDefaultMappings();
    }

    void buttonClicked (Button*)
    {
        AlertWindow::showOkCancelBox (AlertWindow::QuestionIcon,
                                      TRANS("Reset to defaults"),
                                      TRANS("Are you sure you want to reset all the key-mappings to their default state?"),
                                      TRANS("Reset"),
                                      String::empty,
                                      &owner,
                                      ModalCallbackFunction::forComponent (resetToDefaultsCallback, &owner));
    }

private:
    CommandMapEditor& owner;
};


//==============================================================================
CommandMapEditor::CommandMapEditor (KeyPressMappingSet& mappingManager,
                                                      const bool showResetToDefaultButton)
    : mappings (mappingManager),
      resetButton (TRANS ("reset to defaults"))
{
    treeItem = new TopLevelItem (*this);

    if (showResetToDefaultButton)
    {
        addAndMakeVisible (&resetButton);
        resetButton.addListener (treeItem);
    }

    addAndMakeVisible (&tree);
    tree.setColour (TreeView::backgroundColourId, findColour (backgroundColourId));
    tree.setRootItemVisible (false);
    tree.setDefaultOpenness (true);
    tree.setRootItem (treeItem);
}

CommandMapEditor::~CommandMapEditor()
{
    tree.setRootItem (nullptr);
}

//==============================================================================
void CommandMapEditor::setColours (const Colour& mainBackground,
                                            const Colour& textColour)
{
    setColour (backgroundColourId, mainBackground);
    setColour (textColourId, textColour);
    tree.setColour (TreeView::backgroundColourId, mainBackground);
}

void CommandMapEditor::parentHierarchyChanged()
{
    treeItem->changeListenerCallback (nullptr);
}

void CommandMapEditor::resized()
{
    int h = getHeight();

    if (resetButton.isVisible())
    {
        const int buttonHeight = 20;
        h -= buttonHeight + 8;
        int x = getWidth() - 8;

        resetButton.changeWidthToFitText (buttonHeight);
        resetButton.setTopRightPosition (x, h + 6);
    }

    tree.setBounds (0, 0, getWidth(), h);
}

//==============================================================================
bool CommandMapEditor::shouldCommandBeIncluded (const CommandID commandID)
{
    const ApplicationCommandInfo* const ci = mappings.getCommandManager()->getCommandForID (commandID);

    return ci != nullptr && (ci->flags & ApplicationCommandInfo::hiddenFromKeyEditor) == 0;
}

bool CommandMapEditor::isCommandReadOnly (const CommandID commandID)
{
    const ApplicationCommandInfo* const ci = mappings.getCommandManager()->getCommandForID (commandID);

    return ci != nullptr && (ci->flags & ApplicationCommandInfo::readOnlyInKeyEditor) != 0;
}

const String CommandMapEditor::getDescriptionForKeyPress (const KeyPress& key)
{
    return key.getTextDescription();
}

}  // namespace command
}  // namespace rec