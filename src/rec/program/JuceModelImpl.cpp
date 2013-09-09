#include "rec/program/JuceModelImpl.h"

#include "rec/command/Command.pb.h"
#include "rec/data/Address.h"
#include "rec/data/Data.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/program/JuceModel.h"
#include "rec/program/MakeMaps.h"
#include "rec/program/Menu.pb.h"
#include "rec/program/Program.h"

using namespace rec::command;
using namespace rec::data;

namespace rec {
namespace program {

namespace {

void checkMenuEntry(const MenuEntry& menuEntry) {
  int cat = 0;
  if (menuEntry.command_size())
    ++cat;
  if (menuEntry.has_submenu())
    ++cat;
  if (menuEntry.is_recent_files_menu())
    ++cat;
  if (menuEntry.has_callout_function())
    ++cat;

  LOG_IF(DFATAL, cat > 1) << "Ambiguous entry: " << menuEntry.DebugString();
}

}  // namespace

JuceModelImpl::JuceModelImpl(Program* p, JuceModel* juceModel)
    : program_(p),
      juceModel_(juceModel),
      commandMap_(makeCommandMap(*p)),
      menuMap_(makeMenuMap(*p)),
      menuBarMap_(makeMenuBarMap(*p)) {
  auto commands = program_->commands().command();
  for (auto& cmd: commands) {
    if (cmd.has_setter())
      dataListeners_.push_back(make_unique<SetterListener>(cmd, juceModel));
  }

  program_->registerAllCallbacks();

  for (auto& i: commandMap_)
    program_->getCallback(i.first);

  LOG(INFO) << "There are " << commandMap_.size() << " callback entries!!!!";
}

const MenuBar& JuceModelImpl::menuBar() const {
  return menuBarMap_.at(program_->menuBarName());
}

void JuceModelImpl::addSubmenu(PopupMenu* popup,
                                       const MenuEntry& menuEntry) {
  PopupMenu submenu;
  string subname = addMenu(&submenu, menuEntry.submenu());
  popup->addSubMenu(subname, submenu);
}

void JuceModelImpl::addCommand(PopupMenu* popup, CommandID command) {
  popup->addCommandItem(&applicationCommandManager_, command);
}

void JuceModelImpl::addCommands(PopupMenu* popup,
                                  const MenuEntry& menuEntry) {
  for (auto& command: menuEntry.command()) {
    if (command)
      addCommand(popup, command);
    else
      popup->addSeparator();
  }
}

void JuceModelImpl::addMenuEntry(PopupMenu* popup,
                                   const MenuEntry& menuEntry) {
  checkMenuEntry(menuEntry);
  if (menuEntry.command_size())
    addCommands(popup, menuEntry);

  else if (menuEntry.has_submenu())
    addSubmenu(popup, menuEntry);

  else if (menuEntry.is_recent_files_menu())
    makeRecentFiles(popup);

  else if (menuEntry.has_callout_function())
    program_->addMenuEntry(popup, menuEntry);

  else
    popup->addSeparator();
}

string JuceModelImpl::addMenu(PopupMenu* popup, const string& name) {
  string result;
  try {
    const Menu& menu = menuMap_.at(name);
    for (auto& menuEntry: menu.entry())
      addMenuEntry(popup, menuEntry);

    return menu.description().menu(0);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Couldn't get menu " << name;
    return "";
  }
}

void JuceModelImpl::makeRecentFiles(PopupMenu* popup) {
  auto& strategy = program_->recentFilesStrategy();
  vector<string> recentFiles = gui::getRecentFileNames(strategy);
  CommandID command = strategy.getRecentFileCommand();
  for (int i = 0; i < recentFiles.size(); ++i)
    addCommand(popup, command + i);
}

bool JuceModelImpl::perform(const InvocationInfo& info) {
  if (Callback* callback = program_->getCallback(info.commandID)) {
    (*callback)();
    return true;
  }
  LOG(DFATAL) << "No command for " << info.commandID;
  return false;
}

}  // namespace program
}  // namespace rec
