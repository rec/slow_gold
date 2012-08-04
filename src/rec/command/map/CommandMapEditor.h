#ifndef __REC_COMMAND_COMMANDMAPEDITOR__
#define __REC_COMMAND_COMMANDMAPEDITOR__

#include "rec/base/base.h"

using namespace juce;

namespace rec {
namespace command {

class CommandMapEditButton;
class CommandMapTopLevelItem;
class CommandMapItemComponent;
class CommandEntryWindow;

class JUCE_API  CommandMapEditor  : public Component
{
public:
  CommandMapEditor(ApplicationCommandManager& commandManager,
                   ChangeBroadcaster& broadcaster);

    void initialize(bool showResetToDefaultButton);

    virtual void addButton(CommandMapEditButton* button) = 0;
    virtual void removeButton(CommandMapEditButton* button) = 0;
    virtual void addChildren(CommandMapItemComponent* comp) = 0;

    virtual CommandEntryWindow* newWindow() = 0;

    /** Destructor. */
    virtual ~CommandMapEditor();

    void setColours (const Colour& mainBackground,
                     const Colour& textColour);

    virtual bool shouldCommandBeIncluded (CommandID commandID);
    virtual bool isCommandReadOnly (CommandID commandID);

    ApplicationCommandManager& getCommandManager() { return commandManager; }
    ChangeBroadcaster& getChangeBroadcaster() { return broadcaster; }


    /** This can be overridden to let you change the format of the string used
        to describe a keypress.

        This is handy if you're using non-standard KeyPress objects, e.g. for custom
        keys that are triggered by something else externally. If you override the
        method, be sure to let the base class's method handle keys you're not
        interested in.
    */
    // virtual const String getDescriptionForKeyPress (const KeyPress& key);

    //==============================================================================
    /** A set of colour IDs to use to change the colour of various aspects of the editor.

        These constants can be used either via the Component::setColour(), or LookAndFeel::setColour()
        methods.

        To change the colours of the menu that pops up

        @see Component::setColour, Component::findColour, LookAndFeel::setColour, LookAndFeel::findColour
    */
    enum ColourIds
    {
        backgroundColourId  = 0x100ad00,    /**< The background colour to fill the editor background. */
        textColourId        = 0x100ad01,    /**< The colour for the text. */
    };

    //==============================================================================
    /** @internal */
    void parentHierarchyChanged();
    /** @internal */
    void resized();

    static void registerAllTranslations();

protected:
    ApplicationCommandManager& commandManager;
    ChangeBroadcaster& broadcaster;
    TreeView tree;
    TextButton resetButton;

    ScopedPointer<CommandMapTopLevelItem> treeItem;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CommandMapEditor);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPEDITOR__
