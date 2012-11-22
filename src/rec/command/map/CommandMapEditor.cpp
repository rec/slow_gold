#include <math.h>

#include "rec/command/map/CommandMapEditor.h"

#include "rec/base/ArraySize.h"
#include "rec/base/Trans.h"
#include "rec/command/Command.pb.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapEditorMappingItem.h"
#include "rec/command/map/CommandMapTopLevelItem.h"
#include "rec/command/map/CommandEntryWindow.h"
#include "rec/command/map/CommandMapItemComponent.h"

TRAN(RESET_TO_DEFAULTS, "Reset To Factory Default");
TRAN(OK_EDITOR, "OK");
TRAN(CLEAR_EDITOR, "Clear Changes");
TRAN(EXPORT_EDITOR, "Export...");
TRAN(IMPORT_EDITOR, "Import...");

namespace rec {
namespace command {

namespace {

const int BUTTON_HEIGHT = 20;
const double MAX_BUTTON_PADDING = 8.0;
const int BUTTON_Y_PADDING = 8;
const int TOP_RIGHT_PADDING = 10;

}

CommandMapEditor::CommandMapEditor(ApplicationCommandManager& manager,
                                   ChangeBroadcaster& b)
    : commandManager(manager), broadcaster(b),
      resetButton(t_RESET_TO_DEFAULTS),
      clearButton(t_CLEAR_EDITOR),
      exportButton(t_EXPORT_EDITOR),
      importButton(t_IMPORT_EDITOR),
      okButton(t_OK_EDITOR) {
}

void CommandMapEditor::addButton(TextButton* button) {
  addAndMakeVisible(button);
  button->addListener(treeItem);
}

void CommandMapEditor::initialize() {
  treeItem = new CommandMapTopLevelItem(*this);

  addButton(&resetButton);
  addButton(&clearButton);
  addButton(&exportButton);
  addButton(&importButton);
  addButton(&okButton);

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
  int h = getHeight(), w = getWidth();

  TextButton* button[] = {
    &resetButton,
    &importButton,
    &exportButton,
    &clearButton,
    &okButton,
  };

  double totalWidth = 0.0;
  for (uint i = 0; i < arraysize(button); ++i) {
    button[i]->changeWidthToFitText(BUTTON_HEIGHT);
    totalWidth += button[i]->getWidth();
  }

  double padCount = arraysize(button) + 1;
  double padding = juce::jmin((w - totalWidth) / padCount, MAX_BUTTON_PADDING);
  double consumed = totalWidth + padCount * padding;
  double x = juce::jmax(padding + (w - consumed) / 2, 0.0);
  int buttonY = h - TOP_RIGHT_PADDING - BUTTON_HEIGHT;

  for (uint i = 0; i < arraysize(button); ++i) {
    button[i]->setTopLeftPosition(lround(x), buttonY);
    x += (button[i]->getWidth() + padding);
  }

  tree.setBounds(0, 0, getWidth(), h - BUTTON_HEIGHT);
}

static const int RECENT = Command::RECENT_FILES;
static const int BEGIN = CommandIDEncoder::toCommandID(10, RECENT);
static const int END = CommandIDEncoder::toCommandID(100, RECENT);

bool CommandMapEditor::shouldCommandBeIncluded(const CommandID id) {
  if (id >= BEGIN && id <= END)
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
