#include "rec/command/map/CommandMapEditor.h"

#include "rec/base/Trans.h"
#include "rec/command/Command.pb.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapEditorMappingItem.h"
#include "rec/command/map/CommandMapTopLevelItem.h"
#include "rec/command/map/CommandEntryWindow.h"
#include "rec/command/map/CommandMapItemComponent.h"

TRAN(RESET_TO_DEFAULTS, "Reset to default");
TRAN(CLEAR_EDITOR, "Clear all");
TRAN(SAVE_EDITOR, "Save");
TRAN(LOAD_EDITOR, "Load");

namespace rec {
namespace command {

namespace {

const int BUTTON_HEIGHT = 20;
const int BUTTON_X_PADDING = 8;
const int BUTTON_Y_PADDING = 8;
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

void CommandMapEditor::addButton(TextButton* button) {
  addAndMakeVisible(button);
  button->addListener(treeItem);
}

void CommandMapEditor::initialize(const bool showResetToDefaultButton) {
  treeItem = new CommandMapTopLevelItem(*this);

  if (showResetToDefaultButton) {
    addButton(&resetButton);
#if 0
    addButton(&clearButton);
    addButton(&saveButton);
    addButton(&loadButton);
#endif
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
    h -= BUTTON_HEIGHT + BUTTON_Y_PADDING;
    int x = getWidth() - BUTTON_X_PADDING;

    resetButton.changeWidthToFitText(BUTTON_HEIGHT);
    resetButton.setTopRightPosition(x, h + TOP_RIGHT_PADDING);
  }

  tree.setBounds(0, 0, getWidth(), h);
}

static const int RECENT = Command::RECENT_FILES;
static const int BEGIN = CommandIDEncoder::toCommandID(10, RECENT);
static const int END = CommandIDEncoder::toCommandID(100, RECENT);

bool CommandMapEditor::shouldCommandBeIncluded(const CommandID id) {
  if (true && id >= BEGIN && id <= END)
    return false;

  const ApplicationCommandInfo* const ci = commandManager.getCommandForID(id);
  return ci && !(ci->flags & ApplicationCommandInfo::hiddenFromKeyEditor);
}

bool CommandMapEditor::isCommandReadOnly(const CommandID id) {
  const ApplicationCommandInfo* const ci = commandManager.getCommandForID(id);
  DCHECK(ci);
  return ci && (ci->flags & ApplicationCommandInfo::readOnlyInKeyEditor);
}

}  // namespace command
}  // namespace rec
