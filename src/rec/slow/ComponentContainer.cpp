#include "rec/slow/ComponentContainer.h"

#include "rec/gui/RecentFiles.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/Cuttable.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/MakeCallback.h"

using namespace rec::gui;
using namespace rec::command;

namespace rec {
namespace slow {

ComponentContainer::ComponentContainer() : Component("ComponentContainer") {
  addAndMakeVisible(&mainPage_);

  commandManager_.registerAllCommandsForTarget(&target_);
  commandManager_.registerAllCommandsForTarget(JUCEApplication::getInstance());
  addKeyListener(commandManager_.getKeyMappings());

  setContentComponent(this);
  setMenuBar(this);

  setApplicationCommandManagerToWatch(&commandManager_);
  setUsingNativeTitleBar(true);
  setVisible(true);
};

ComponentContainer::~ComponentContainer() {
#if JUCE_WIN32 || JUCE_LINUX
  // deleteAndZero (taskbarIcon);
#endif

  // because we've set the content comp to be used as our menu bar model, we
  // have to switch this off before deleting the content comp..
  setMenuBar(NULL);

#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
  // Why isn't this in GenericApplication?
  MenuBarModel::setMacMainMenu(NULL);
#endif
}

void ComponentContainer::clearTree() {
  persist::data<file::VirtualFileList>()->clear();
}

void ComponentContainer::clearFile() {
  persist::data<file::VirtualFile>()->clear();
}

void ComponentContainer::audioPreferences() {
  juce::DialogWindow::showModalDialog("Set Audio Preferences",
                                      mainPage_.audioSetupPage(),
                                      mainPage_.get(),
                                      Colours::white, true);
}

void ComponentContainer::resized() {
  mainComponent_.setBounds(0, 0, getWidth(), getHeight());
}

const StringArray ComponentContainer::getMenuBarNames() {
  static const char* const names[] = {"File", "Edit", NULL};
  return StringArray(names);
}

static const int RECENT_FILES_OFFSET = 1000;  // hack

const PopupMenu ComponentContainer::getMenuForIndex(int menuIndex,
                                                    const String& menuName) {
  using rec::command::Command;

  PopupMenu menu;
  if (menuName == "File") {
    menu.addItem(OPEN, "Open...");
    menu.addItem(CLOSE, "Close");

    gui::RecentFiles recent = gui::getSortedRecentFiles();
    PopupMenu submenu;
    for (int i = 0; i < recent.file_size(); ++i)
      submenu.addItem(RECENT_FILES_OFFSET + i, getFilename(recent.file(i).file()));

    menu.addSubMenu("Open recent", submenu);
    menu.addItem(EJECT, "Eject all discs");
    menu.addItem(QUIT, "Quit");

  } else if (menuName == "Edit") {
    menu.addItem(CUT, "Cut", canCutOrCopy());
    menu.addItem(COPY, "Copy", canCutOrCopy());
    menu.addItem(PASTE, "Paste", canPaste());
    menu.addItem(CLEAR_FILE, "Clear file");
    menu.addItem(CLEAR_SELECTION, "Clear selection of loop points");
    menu.addItem(CLEAR_LOOPS, "Clear loops");
    menu.addItem(CLEAR_TIME, "Clear time and pitch shift to 1");
    menu.addItem(TREE_CLEAR, "Clear bookmarks area");
    menu.addItem(AUDIO_PREFERENCES, "Set audio preferences...");
  }

  return menu;
}

void ComponentContainer::menuItemSelected(int menuItemID, int menuIndex) {
  thread::callAsync(this, &ComponentContainer::doMenuItemSelected,
                    menuItemID, menuIndex);
}

void ComponentContainer::doMenuItemSelected(int itemID, int topLevelMenuIndex) {
  if (itemID < RECENT_FILES) {
    Command::Type command = static_cast<Command:Type>(itemID);
    if (!commandMap_.execute(command))
      LOG(ERROR) << "Couldn't execute" << Command::Type_Name(command);
  } else {
    mainComponent_.loadRecentFile(itemID - RECENT_FILES);
  }
}

ApplicationCommandTarget* ComponentContainer::getNextCommandTarget() {
  return findFirstTargetParentComponent();
}


}  // namespace slow
}  // namespace rec
