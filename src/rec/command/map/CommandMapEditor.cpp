#include "rec/command/map/CommandMapEditor.h"

#include "rec/base/Trans.h"
#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapEditorMappingItem.h"
#include "rec/command/map/CommandMapTopLevelItem.h"
#include "rec/command/map/CommandEntryWindow.h"
#include "rec/command/map/CommandMapItemComponent.h"

TRAN(RESET_TO_DEFAULTS, "Reset to default settings.");
TRAN(CLEAR_EDITOR, "Clear all assignments.");
TRAN(SAVE_EDITOR, "Save current assignments to file.");
TRAN(LOAD_EDITOR, "Load assignments from file.");

namespace rec {
namespace command {

namespace {

const int BUTTON_HEIGHT = 20;
const int BUTTON_PADDING = 8;
const int TOP_RIGHT_PADDING = 6;

}

CommandMapEditor::CommandMapEditor(ApplicationCommandManager& manager,
                                   ChangeBroadcaster& b)
    : commandManager(manager), broadcaster(b),
      resetButton(t_RESET_TO_DEFAULTS),
      clearButton(t_CLEAR_EDITOR),
      saveButton(t_SAVE_EDITOR),
      loadButton(t_LOAD_EDITOR) {
}

void CommandMapEditor::initialize(const bool showResetToDefaultButton) {
  treeItem = new CommandMapTopLevelItem(*this);

  if (showResetToDefaultButton) {
    addAndMakeVisible(&resetButton);
    resetButton.addListener(treeItem);
  }

  addAndMakeVisible(&tree);
  tree.setColour(TreeView::backgroundColourId, findColour(backgroundColourId));
  tree.setRootItemVisible(false);
  tree.setDefaultOpenness(false);
  tree.setRootItem(treeItem);
}

CommandMapEditor::~CommandMapEditor() {
  tree.setRootItem(NULL);
}

void CommandMapEditor::setColours(const Colour& mainBackground,
                                   const Colour& textColour) {
  setColour(backgroundColourId, mainBackground);
  setColour(textColourId, textColour);
  tree.setColour(TreeView::backgroundColourId, mainBackground);
}

void CommandMapEditor::parentHierarchyChanged() {
  treeItem->changeListenerCallback(NULL);
}

void CommandMapEditor::resized() {
  int h = getHeight();

  if (resetButton.isVisible()) {
    h -= BUTTON_HEIGHT + BUTTON_PADDING;
    int x = getWidth() - BUTTON_PADDING;

    resetButton.changeWidthToFitText(BUTTON_HEIGHT);
    resetButton.setTopRightPosition(x, h + TOP_RIGHT_PADDING);
  }

  tree.setBounds(0, 0, getWidth(), h);
}

//==============================================================================
bool CommandMapEditor::shouldCommandBeIncluded(const CommandID id) {
  const ApplicationCommandInfo* const ci = commandManager.getCommandForID(id);

  return ci && !(ci->flags & ApplicationCommandInfo::hiddenFromKeyEditor);
}

bool CommandMapEditor::isCommandReadOnly(const CommandID id) {
  const ApplicationCommandInfo* const ci = commandManager.getCommandForID(id);
  return ci && !(ci->flags & ApplicationCommandInfo::readOnlyInKeyEditor);
}

}  // namespace command
}  // namespace rec
