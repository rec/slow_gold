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
#include "rec/gui/Dialog.h"

TRAN(RESET_TO_DEFAULTS, "Reset To Factory Default");
TRAN(CLEAR_EDITOR, "Clear Changes");
TRAN(EXPORT_EDITOR, "Export...");
TRAN(IMPORT_EDITOR, "Import...");
TRAN(SURE_YOU_RESET, "Are you sure you want to reset all the command "
     "assignments to their default state?");
TRAN(SURE_YOU_CLEAR, "Are you sure you want to clear all your changes?");
TRAN(RESET, "Reset");
TRAN(CHOOSE_EXPORT_FILE, "Choose A New File For Export");
TRAN(CHOOSE_IMPORT_FILE, "Open A File For Import");

namespace rec {
namespace command {

namespace {

const int BUTTON_HEIGHT = 20;
const double MAX_BUTTON_PADDING = 8.0;
const int BUTTON_Y_PADDING = 8;
const int TOP_RIGHT_PADDING = 10;

}

CommandMapEditor::CommandMapEditor(ApplicationCommandManager* manager,
                                   ChangeBroadcaster* b)
    : commandManager_(manager), broadcaster_(b),
      resetButton_(t_RESET_TO_DEFAULTS),
      clearButton_(t_CLEAR_EDITOR),
      exportButton_(t_EXPORT_EDITOR),
      importButton_(t_IMPORT_EDITOR),
      okButton_(t_OK) {
}

void CommandMapEditor::addButton(TextButton* button) {
  addAndMakeVisible(button);
  button->addListener(this);
}

void CommandMapEditor::initialize() {
  addButton(&resetButton_);
  addButton(&clearButton_);
  addButton(&exportButton_);
  addButton(&importButton_);
  addButton(&okButton_);

  addAndMakeVisible(&tree);
  tree.setColour(TreeView::backgroundColourId, findColour(backgroundColourId));
  tree.setRootItemVisible(false);
  tree.setDefaultOpenness(false);
  resetTreeItem();
}

void CommandMapEditor::resetTreeItem() {
  if (treeItem_)
    tree.setRootItem(NULL);
  treeItem_.reset(new CommandMapTopLevelItem(*this));
  tree.setRootItem(treeItem_.get());
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
  treeItem_->changeListenerCallback(NULL);
}

void CommandMapEditor::resized() {
  int h = getHeight(), w = getWidth();

  TextButton* button[] = {
    &resetButton_,
    &importButton_,
    &exportButton_,
    &clearButton_,
    &okButton_,
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

  tree.setBounds(0, 0, getWidth(), h - BUTTON_HEIGHT - 2 * TOP_RIGHT_PADDING);
}

static const int RECENT = Command::RECENT_FILES;
static const int BEGIN = CommandIDEncoder::toCommandID(10, RECENT);
static const int END = CommandIDEncoder::toCommandID(100, RECENT);

bool CommandMapEditor::shouldCommandBeIncluded(const CommandID id) {
  if (id >= BEGIN && id <= END)
    return false;

  const ApplicationCommandInfo* const ci = commandManager_->getCommandForID(id);
  return ci && !(ci->flags & ApplicationCommandInfo::hiddenFromKeyEditor);
}

bool CommandMapEditor::isCommandReadOnly(const CommandID id) {
  const ApplicationCommandInfo* const ci = commandManager_->getCommandForID(id);
  DCHECK(ci);
  return ci && (ci->flags & ApplicationCommandInfo::readOnlyInKeyEditor);
}

void CommandMapEditor::buttonClicked(Button* button) {
  if (button == &resetButton_)
    resetButton();
  else if (button == &clearButton_)
    clearButton();
  else if (button == &exportButton_)
    exportButton();
  else if (button == &importButton_)
    importButton();
  else if (button == &okButton_)
    okButton();
}

void CommandMapEditor::okButton() {
  using namespace juce;
  if (DocumentWindow* dw = dynamic_cast<DocumentWindow*>(getParentComponent()))
    dw->closeButtonPressed();
  else
    LOG(DFATAL) << "Parent window wasn't a document window!";
}

using namespace rec::gui::dialog;

void CommandMapEditor::exportButton() {
  expectingExport_ = true;
  saveVirtualFile(this, "import export", t_CHOOSE_EXPORT_FILE, "*.slow");
}

void CommandMapEditor::importButton() {
  expectingExport_ = false;
  saveVirtualFile(this, "import export", t_CHOOSE_IMPORT_FILE, "*.slow");
}

void CommandMapEditor::operator()(const File& f) {
  if (expectingExport_) {
    doExport(f);
  } else {
    doImport(f);
    resetTreeItem();
  }
}

static void resetCallback(int result, CommandMapEditor* owner) {
  if (result) {
    owner->doReset();
    owner->resetTreeItem();
  }
}

static void clearCallback(int result, CommandMapEditor* owner) {
  if (result) {
    owner->doClear();
    owner->resetTreeItem();
  }
}

void CommandMapEditor::resetButton() {
  AlertWindow::showOkCancelBox(
      AlertWindow::QuestionIcon,
      t_RESET_TO_DEFAULTS,
      t_SURE_YOU_RESET,
      t_RESET,
      t_CANCEL,
      this,
      ModalCallbackFunction::forComponent(resetCallback, this));
}

void CommandMapEditor::clearButton() {
  AlertWindow::showOkCancelBox(
      AlertWindow::QuestionIcon,
      t_CLEAR_EDITOR,
      t_SURE_YOU_CLEAR,
      t_CLEAR_EDITOR,
      t_CANCEL,
      this,
      ModalCallbackFunction::forComponent(clearCallback, this));
}


}  // namespace command
}  // namespace rec
