#include "rec/app/ProgramInstanceImpl.h"
#include "rec/app/Program.h"
#include "rec/command/Command.pb.h"
#include "rec/app/Menu.pb.h"

using namespace rec::command;

namespace rec {
namespace app {

namespace {

typedef ProgramInstance::Impl::ProgramMap ProgramMap;
typedef ProgramInstance::Impl::MenuMap MenuMap;
typedef ProgramInstance::Impl::MenuBarMap MenuBarMap;

ProgramMap makeProgramMap(const Program& program) {
  ProgramMap programMap;
  for (auto& command: program.commands().command())
    programMap[command.command()] = command;

  for (auto& command: program.keypresses().command()) {
    try {
      *programMap.at(command.command()).mutable_keypress() = command.keypress();
    } catch (const std::out_of_range&) {
      LOG(DFATAL) << "Out of range keypress command." << command.command();
    }
  }
  return programMap;
}

MenuMap makeMenuMap(const Program& program) {
  MenuMap menuMap;
  for (auto& menu: program.menus().menu())
    menuMap[menu.description().name()] = menu;
  return menuMap;
}

MenuBarMap makeMenuBarMap(const Program& program) {
  MenuBarMap menuBarMap;
  for (auto& menuBar: program.menuCollection().menu_bar())
    menuBarMap[menuBar.description().name()] = menuBar;
  return menuBarMap;
}

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

ProgramInstance::Impl::Impl(Program* p)
    : program_(p),
      programMap_(makeProgramMap(*p)),
      menuMap_(makeMenuMap(*p)),
      menuBarMap_(makeMenuBarMap(*p)) {
}

const MenuBar& ProgramInstance::Impl::menuBar() const {
  return menuBarMap_.at(program_->menuBarName());
}

void ProgramInstance::Impl::addSubmenu(PopupMenu* popup, const MenuEntry& menuEntry) {
  PopupMenu submenu;
  string subname = addMenu(&submenu, menuEntry.submenu());
  popup->addSubMenu(subname, submenu);
}

void ProgramInstance::Impl::addCommand(PopupMenu* popup, CommandID command) {
  popup->addCommandItem(&applicationCommandManager_, command);
}

void ProgramInstance::Impl::addCommands(PopupMenu* popup, const MenuEntry& menuEntry) {
  for (auto& command: menuEntry.command()) {
    if (command)
      addCommand(popup, command);
    else
      popup->addSeparator();
  }
}

void ProgramInstance::Impl::addMenuEntry(PopupMenu* popup, const MenuEntry& menuEntry) {
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

string ProgramInstance::Impl::addMenu(PopupMenu* popup, const string& name) {
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

void ProgramInstance::Impl::makeRecentFiles(PopupMenu* popup) {
  auto& strategy = program_->recentFilesStrategy();
  vector<string> recentFiles = gui::getRecentFileNames(&strategy);
  CommandID command = strategy.getRecentFileCommand();
  for (int i = 0; i < recentFiles.size(); ++i)
    addCommand(popup, command + i);
}

}  // namespace app
}  // namespace rec

