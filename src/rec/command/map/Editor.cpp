#include <math.h>

#include "rec/command/map/Editor.h"

#include "rec/base/ArraySize.h"
#include "rec/base/Trans.h"
#include "rec/command/Command.pb.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/map/EditButton.h"
#include "rec/command/map/MapItem.h"
#include "rec/command/map/EntryWindow.h"
#include "rec/command/map/MapItemComponent.h"
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
TRAN(CURRENTLY_ASSIGNED, "Currently assigned to");

TRAN(CHANGE_KEY_MAPPING, "Change key-mapping");
TRAN(THIS_KEY_ASSIGNED, "This key is already assigned to the command");
TRAN(WANT_TO_REASSIGN, "Do you want to re-assign it to this new command instead?");
TRAN(REASSIGN, "Re-assign");

namespace rec {
namespace command {

namespace {

class TopLevelItem : public TreeViewItem, public ChangeListener {
 public:
  TopLevelItem(Editor* editor) : editor_(editor) {
    setLinesDrawnForSubItems(false);
    editor_->getChangeBroadcaster()->addChangeListener(this);
  }

  ~TopLevelItem() {
    editor_->getChangeBroadcaster()->removeChangeListener(this);
  }

  void changeListenerCallback(ChangeBroadcaster*) {
    DLOG(INFO) << "TODO: changeListenerCallback";
  }

  bool mightContainSubItems() { return true; }
  String getUniqueName() const { return "keys"; }

  void changeListenerCallback(ChangeBroadcaster*);

 protected:
  Editor* editor_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(TopLevelItem);
};


const int BUTTON_HEIGHT = 20;
const double MAX_BUTTON_PADDING = 8.0;
const int BUTTON_Y_PADDING = 8;
const int TOP_RIGHT_PADDING = 10;

String currentlyAssignedTo(const String& commandName) {
  return str("\n\n(" + t_CURRENTLY_ASSIGNED + " \"" + commandName + "\")");
}

bool showCommandMapBox(const String& command, Component* comp,
                       ModalComponentManager::Callback* cb) {
  return AlertWindow::showOkCancelBox(
      AlertWindow::WarningIcon,
      t_CHANGE_KEY_MAPPING,
      str(t_THIS_KEY_ASSIGNED + " \"" + command +
          "\"\n\n" + t_WANT_TO_REASSIGN),
      t_REASSIGN, t_CANCEL, comp, cb);
}

void addTextButton(Editor* editor, TextButton* button) {
  editor->addAndMakeVisible(button);
  button->addListener(editor);
}

const int RECENT = Command::RECENT_FILES;
const int BEGIN = CommandIDEncoder::toCommandID(10, RECENT);
const int END = CommandIDEncoder::toCommandID(100, RECENT);

}

Editor::Editor(ApplicationCommandManager* manager,
                                   CommandMap* map)
    : commandManager_(manager),
      commandMap_(map),
      resetButton_(t_RESET_TO_DEFAULTS),
      clearButton_(t_CLEAR_EDITOR),
      exportButton_(t_EXPORT_EDITOR),
      importButton_(t_IMPORT_EDITOR),
      okButton_(t_OK),
      commandMapEditButton_(NULL) {
}

void Editor::initialize() {
  addTextButton(this, &resetButton_);
  addTextButton(this, &clearButton_);
  addTextButton(this, &exportButton_);
  addTextButton(this, &importButton_);
  addTextButton(this, &okButton_);

  addAndMakeVisible(&tree);
  tree.setColour(TreeView::backgroundColourId, findColour(backgroundColourId));
  tree.setRootItemVisible(false);
  tree.setDefaultOpenness(false);
  resetTreeItem();
}

void Editor::resetTreeItem() {
  if (topLevelItem_)
    tree.setRootItem(NULL);
  topLevelItem_.reset(new TopLevelItem(this));
  tree.setRootItem(topLevelItem_.get());
}

Editor::~Editor() {
  tree.setRootItem(NULL);
}

void Editor::setColours(const Colour& mainBackground,
                                   const Colour& textColour) {
  setColour(backgroundColourId, mainBackground);
  setColour(textColourId, textColour);
  tree.setColour(TreeView::backgroundColourId, mainBackground);
}

void Editor::parentHierarchyChanged() {
  topLevelItem_->changeListenerCallback(NULL);
}

void Editor::resized() {
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

static TopLevelItem* createTopLevelItem(ApplicationCommandManager* acm,
                                        Editor* editor) {
}

void Editor::fillTopLevelItem() {
  topLevelItem_.reset(new TopLevelItem);

  StringArray categories(acm->getCommandCategories());
  categories.sort(false);

  for (int i = 0; i < categories.size(); ++i) {
    const String& cat = categories[i];
    const Array<CommandID> commands(acm->getCommandsInCategory(cat));
    const Array<CommandID> goodCommands;
    TreeView* categoryItem = NULL;

    for (int j = commands.size() - 1; j >= 0; ++j) {
      CommandID id = commands[j];
      if (id >= BEGIN && id <= END)
        continue;
      if (const ApplicationCommandInfo* const info = acm->getCommandForID(id)) {
        if (!(info->flags & ApplicationCommandInfo::hiddenFromKeyEditor)) {
          if (!categoryItem) {
            categoryItem = new CategoryItem(this, cat);
            topLevelItem_->addSubItem(categoryItem);
          }
          ptr<MapItem> mapItem(new MapItem(this, id));
          mapItemMap_[id] = mapItem.get();
          categoryItem->addSubItem(mapItem.transfer());
        }
      }
    }
  }
}


bool Editor::isCommandReadOnly(const CommandID id) {
  const ApplicationCommandInfo* const ci = commandManager_->getCommandForID(id);
  DCHECK(ci);
  return ci && (ci->flags & ApplicationCommandInfo::readOnlyInKeyEditor);
}

void Editor::buttonClicked(Button* button) {
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

void Editor::okButton() {
  using namespace juce;
  if (DocumentWindow* dw = dynamic_cast<DocumentWindow*>(getParentComponent()))
    dw->closeButtonPressed();
  else
    LOG(DFATAL) << "Parent window wasn't a document window!";
}

using namespace rec::gui::dialog;

void Editor::exportButton() {
  expectingExport_ = true;
  saveVirtualFile(this, "import export", t_CHOOSE_EXPORT_FILE, "*.slow");
}

void Editor::importButton() {
  expectingExport_ = false;
  saveVirtualFile(this, "import export", t_CHOOSE_IMPORT_FILE, "*.slow");
}

void Editor::operator()(const File& f) {
  if (expectingExport_) {
    doExport(f);
  } else {
    doImport(f);
    resetTreeItem();
  }
}

static void resetCallback(int result, Editor* editor) {
  if (result) {
    editor->doReset();
    editor->resetTreeItem();
  }
}

static void clearCallback(int result, Editor* editor) {
  if (result) {
    editor->doClear();
    editor->resetTreeItem();
  }
}

void Editor::resetButton() {
  AlertWindow::showOkCancelBox(
      AlertWindow::QuestionIcon,
      t_RESET_TO_DEFAULTS,
      t_SURE_YOU_RESET,
      t_RESET,
      t_CANCEL,
      this,
      ModalCallbackFunction::forComponent(resetCallback, this));
}

void Editor::clearButton() {
  AlertWindow::showOkCancelBox(
      AlertWindow::QuestionIcon,
      t_CLEAR_EDITOR,
      t_SURE_YOU_CLEAR,
      t_CLEAR_EDITOR,
      t_CANCEL,
      this,
      ModalCallbackFunction::forComponent(clearCallback, this));
}

const String Editor::getKeyMessage(const string& key) {
  String message(name() + ": " + getDescription(key));
  const CommandID previousCommand = getCommand(key);
  if (previousCommand) {
    String pn = getCommandManager()->getNameOfCommand(previousCommand);
    message += currentlyAssignedTo(pn);
  }

  return message;
}

void Editor::addChildren(MapItemComponent* comp) {
  CommandID command = comp->commandID_;
  const bool isReadOnly = isCommandReadOnly(command);
  KeyArray keys = getKeys(command);
  for (int i = 0; i < jmin(MAX_NUM_ASSIGNMENTS, keys.size()); ++i)
    comp->addButton(getDescription(keys[i]), i, isReadOnly);
  comp->addButton(String::empty, -1, isReadOnly);
}

void Editor::assignNewKey(EditButton* button,
                                    const string& key) {
  removeKey(key);
  if (button->keyNum >= 0)
    removeKey(button->commandID, button->keyNum);
  addKey(button->commandID, key, button->keyNum);
}

static void assignNewKeyCallback(int result, Editor* button,
                                 const string key) {
  if (result)
    button->getEditor().assignNewKey(button, key);
}

void Editor::setNewKey(EditButton* button,
                                 const string& key) {
  if (isValid(key)) {
    const CommandID previousCommand = getCommand(newKey);
    if (previousCommand == 0) {
      assignNewKey(button, key);
    } else {
      showCommandMapBox(commandManager_->getNameOfCommand(previousCommand),
                        this,
                        ModalCallbackFunction::forComponent(
                            assignNewKeyCallback, button, key));
    }
  }
}

void Editor::keyChosen(EditButton* button) {
  setNewKey(button, key_);
  if (commandEntryWindow_)
    commandEntryWindow_.reset();
}

static void keyChosen(int result, EditButton* button) {
  if (result)
    button->getEditor()->keyChosen(button);
}

void Editor::buttonMenuCallback(int result,
                                          EditButton* button) {
  if (result == 1) {
    commandEntryWindow_.reset(newWindow());
    commandEntryWindow_->enterModalState(true,
        ModalCallbackFunction::forComponent(keyChosen, button));
  } else if (result == 2) {
    removeKey(button->commandID, button->keyNum);
  }
}

void Editor::setKey(const string& key) {
  key_ = key;
  if (commandEntryWindow_) {
    String msg = getKeyMessage(key);
    thread::callAsync(commandEntryWindow_.get(),
                      &EntryWindow::setMessage, msg);
  } else {
    LOG(DFATAL) << "Tried to set last key with no window up";
  }
}

CommandID Editor::getCommand(const string& key) {
  return static_cast<CommandID>(mappings_->getCommand(key));
}

void Editor::removeKeyAtIndex(CommandID command, int keyNum) {
  mappings_->removeCommand(static_cast<Command::Type>(command), keyNum);
  mappings_->sendChangeMessage();
}

void Editor::removeKey(const string& key) {
  mappings_->removeKey(key);
  mappings_->sendChangeMessage();
}

void Editor::addKey(CommandID cmd, const string& key, int keyIndex) {
  DLOG(INFO) << "adding key " << cmd << ", " << keyIndex;
  Command::Type c = static_cast<Command::Type>(cmd);
  if (keyIndex >= 0)
    mappings_->addAtIndex(key, c, keyIndex);
  mappings_->sendChangeMessage();
}

Editor::KeyArray Editor::getKeys(CommandID c) {
  vector<string> keys(mappings_->getKeys(static_cast<Command::Type>(c)));
  KeyArray result;

  for (uint i = 0; i < keys.size(); ++i)
    result[i] = keys[i];
  return result;
}

}  // namespace command
}  // namespace rec
