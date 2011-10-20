#include "rec/command/map/CommandMapEditor.h"
#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapEditorMappingItem.h"
#include "rec/command/map/CommandMapTopLevelItem.h"
#include "rec/command/map/CommandEntryWindow.h"
#include "rec/command/map/CommandMapItemComponent.h"

namespace rec {
namespace command {

//==============================================================================
CommandMapEditor::CommandMapEditor(ApplicationCommandManager& manager,
                                   ChangeBroadcaster& b)
    : commandManager(manager), broadcaster(b), resetButton (TRANS ("reset to defaults"))
{
}

void CommandMapEditor::initialize(const bool showResetToDefaultButton) {
    treeItem = new CommandMapTopLevelItem(*this);

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
    const ApplicationCommandInfo* const ci = commandManager.getCommandForID (commandID);

    return ci != nullptr && (ci->flags & ApplicationCommandInfo::hiddenFromKeyEditor) == 0;
}

bool CommandMapEditor::isCommandReadOnly (const CommandID commandID)
{
    const ApplicationCommandInfo* const ci = commandManager.getCommandForID (commandID);

    return ci != nullptr && (ci->flags & ApplicationCommandInfo::readOnlyInKeyEditor) != 0;
}

}  // namespace command
}  // namespace rec
