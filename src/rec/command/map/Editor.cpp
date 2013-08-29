#include <math.h>

#include <algorithm>

#include "rec/command/map/Editor.h"

#include "rec/base/ArraySize.h"
#include "rec/base/Trans.h"
#include "rec/command/Command.pb.h"
#include "rec/command/ID.h"
#include "rec/command/map/EditButton.h"
#include "rec/command/map/CommandMap.h"
#include "rec/command/map/Items.h"
#include "rec/gui/Dialog.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/ModalCallback.h"

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
TRAN(NEW_COMMAND_MAPPING, "New command mapping");

namespace rec {
namespace command {

using namespace juce;

namespace {

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
}

const ID RECENT(Command::RECENT_FILES);
const ID BEGIN(RECENT, 10);
const ID END(RECENT, 100);

}

Editor::Editor(ApplicationCommandManager* manager, CommandMap* map)
    : commandManager_(manager),
      commandMap_(map),
      resetButton_(t_RESET_TO_DEFAULTS),
      clearButton_(t_CLEAR_EDITOR),
      exportButton_(t_EXPORT_EDITOR),
      importButton_(t_IMPORT_EDITOR),
      okButton_(t_OK),
      wasChanged_(false) {
}

void Editor::initialize() {
  addTextButton(this, &resetButton_);
  addTextButton(this, &clearButton_);
  addTextButton(this, &exportButton_);
  addTextButton(this, &importButton_);
  addTextButton(this, &okButton_);

  fillTopLevelItem();

  addAndMakeVisible(&tree_);
  tree_.setColour(TreeView::backgroundColourId, findColour(backgroundColourId));
  tree_.setRootItemVisible(false);
  tree_.setDefaultOpenness(false);

}

Editor::~Editor() {}

void Editor::setColours(const Colour& mainBackground,
                                   const Colour& textColour) {
  setColour(backgroundColourId, mainBackground);
  setColour(textColourId, textColour);
  tree_.setColour(TreeView::backgroundColourId, mainBackground);
}

juce::AlertWindow* Editor::newWindow() {
  ptr<juce::AlertWindow> window(new juce::AlertWindow(t_NEW_COMMAND_MAPPING,
                                                      getWindowTitle(),
                                                      AlertWindow::NoIcon));

  window->addButton(t_OK, 1);
  window->addButton(t_CANCEL, 0);

  // Probably not needed in the general case but no harm...
  // (avoid return + escape keys getting processed by the buttons..)
  for (int i = window->getNumChildComponents(); --i >= 0;)
    window->getChildComponent(i)->setWantsKeyboardFocus(false);

  window->setWantsKeyboardFocus(true);
  window->grabKeyboardFocus();
  return window.release();
}

void Editor::parentHierarchyChanged() {
  // topLevelItem_->changeListenerCallback(nullptr); // TODO
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

  tree_.setBounds(0, 0, getWidth(), h - BUTTON_HEIGHT - 2 * TOP_RIGHT_PADDING);
}

namespace {

struct CompareCommands {
  explicit CompareCommands(ApplicationCommandManager* manager = nullptr)
      : manager_(manager) {
  }

  bool operator()(const ID& x, const ID& y) const {
    return name(x) > name(y);
  }

  String name(ID id) const {
    const ApplicationCommandInfo* info = manager_->getCommandForID(id);
    return info ? info->shortName : String("");
  }
  ApplicationCommandManager *manager_;
};

}  // namespace

void Editor::fillTopLevelItem() {
  topLevelItem_.reset(new Item("top", "", true));
  topLevelItem_->setLinesDrawnForSubItems(false);
  tree_.setRootItem(topLevelItem_.get());

  StringArray categories(commandManager_->getCommandCategories());
  categories.sort(false);

  for (int i = 0; i < categories.size(); ++i) {
    const String& cat = categories[i];
    Array<CommandID> commands(commandManager_->getCommandsInCategory(cat));
    std::sort(commands.begin(), commands.end(),
              CompareCommands(commandManager_));
    TreeViewItem* categoryItem = nullptr;

    for (int j = commands.size() - 1; j >= 0; --j) {
      ID id = commands[j];
      if ((id >= BEGIN && id <= END) ||
          commandHasFlags(id, ApplicationCommandInfo::hiddenFromKeyEditor)) {
        continue;
      }
      const ApplicationCommandInfo* info = commandManager_->getCommandForID(id);
      if (!categoryItem) {
        categoryItem = new CategoryItem(cat, this);
        topLevelItem_->addSubItem(categoryItem);
      }
      MapItem* mapItem(new MapItem(this, id, info->shortName));
      categoryItem->addSubItem(mapItem);
      mapItemMap_[id] = mapItem;
    }
  }
}

bool Editor::commandHasFlags(ID id, int flags) const {
  const ApplicationCommandInfo* const ci = commandManager_->getCommandForID(id);
  DCHECK(ci);
  return ci && (ci->flags & flags);
}

// TODO: this isn't hooked in.
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
  gui::dialog::saveVirtualFile(this, "import export", t_CHOOSE_EXPORT_FILE,
                               "*.slow");

  // TODO: one of these must be wrong.
}

void Editor::importButton() {
  expectingExport_ = false;
  gui::dialog::saveVirtualFile(this, "import export", t_CHOOSE_IMPORT_FILE,
                               "*.slow");
  wasChanged_ = false;
}

void Editor::operator()(const File& f) {
  if (expectingExport_)
    exportToFile(f);
  else
    importFromFile(f);
}

void Editor::exportToFile(const File&) {
  // TODO
}

void Editor::importFromFile(const File&) {
  // TODO
  wasChanged_ = false;
}


void Editor::reset(int returnValue) {
  if (returnValue) {
    // TODO
    wasChanged_ = false;
  }
}
void Editor::clear(int returnValue) {
  if (returnValue) {
    // TODO
    wasChanged_ = false;
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
      thread::modalCallback(this, &Editor::reset));
}

void Editor::clearButton() {
  AlertWindow::showOkCancelBox(
      AlertWindow::QuestionIcon,
      t_CLEAR_EDITOR,
      t_SURE_YOU_CLEAR,
      t_CLEAR_EDITOR,
      t_CANCEL,
      this,
      thread::modalCallback(this, &Editor::clear));
}

const String Editor::getKeyMessage(const string& key) {
  String message(name() + ": " + getDescription(key));
  const ID previousCommand = getCommand(key);
  if (previousCommand) {
    String pn = getCommandManager()->getNameOfCommand(previousCommand);
    message += currentlyAssignedTo(pn);
  }

  return message;
}

void Editor::addChildren(MapItemComponent* comp) {
  ID id = comp->commandID_;
  bool isReadOnly = commandHasFlags(
     id, ApplicationCommandInfo::readOnlyInKeyEditor);
  KeyArray keys = getKeys(id);
  for (int i = 0; i < jmin(MAX_NUM_ASSIGNMENTS, keys.size()); ++i)
    comp->createEditButton(getDescription(keys[i]), i, isReadOnly);
  comp->createEditButton(String::empty, -1, isReadOnly);
}

void Editor::assignNewKey(EditButton* button, const string& key, int result) {
  if (result) {
    removeKey(key);
    if (button->keyNum_ >= 0)
      removeKeyAtIndex(button->id_, button->keyNum_);
    addKey(button->id_, key, button->keyNum_);
    wasChanged_ = true;
  }
}

void Editor::setNewKey(EditButton* button, const string& key) {
  if (isValid(key)) {
    const ID previousCommand = getCommand(key);
    if (previousCommand == 0) {
      assignNewKey(button, key);
    } else {
      showCommandMapBox(commandManager_->getNameOfCommand(previousCommand),
                        this,
                        thread::modalCallback(this, &Editor::assignNewKey,
                                              button, key));
    }
  }
}

void Editor::keyChosen(EditButton* button, int result) {
  if (result) {
    setNewKey(button, key_);
    if (entryWindow_)
      entryWindow_.reset();
  }
}

void Editor::buttonMenuCallback(EditButton* button, int result) {
  if (result == 1) {
    entryWindow_.reset(newWindow());
    entryWindow_->enterModalState(true, thread::modalCallback(
        this, &Editor::keyChosen, button));

  } else if (result == 2) {
    removeKeyAtIndex(button->id_, button->keyNum_);
  }
}

void Editor::setKey(const string& key) {
  key_ = key;
  if (entryWindow_) {
    String msg = getKeyMessage(key);
    thread::callAsync(entryWindow_.get(), &AlertWindow::setMessage, msg);
  } else {
    LOG(DFATAL) << "Tried to set last key with no window up";
  }
}

ID Editor::getCommand(const string& key) {
  return ID(commandMap_->getCommand(key));
}

ChangeBroadcaster* Editor::getChangeBroadcaster() {
  return commandMap_;
}

void Editor::removeKeyAtIndex(ID id, int keyNum) {
  commandMap_->removeCommand(id, keyNum);
  commandMap_->sendChangeMessage();
  wasChanged_ = true;
}

void Editor::removeKey(const string& key) {
  commandMap_->removeKey(key);
  commandMap_->sendChangeMessage();
}

void Editor::addKey(ID cmd, const string& key, int keyIndex) {
  DLOG(INFO) << "adding key " << cmd << ", " << keyIndex;
  if (keyIndex >= 0)
    commandMap_->addAtIndex(key, cmd, keyIndex);
  commandMap_->sendChangeMessage();
  wasChanged_ = true;
}

Editor::KeyArray Editor::getKeys(ID id) {
  // TODO: needs to take the index into account...
  vector<string> keys(commandMap_->getKeys(id));
  KeyArray result;

  for (uint i = 0; i != keys.size(); ++i)
    result.add(keys[i]);
  return result;
}

}  // namespace command
}  // namespace rec
