#include <stdexcept>

#include "rec/app/ProgramInstance.h"
#include "rec/app/Program.h"
#include "rec/command/Command.pb.h"
#include "rec/app/Menu.pb.h"

namespace rec {
namespace app {

using namespace rec::command;

namespace {

typedef std::unordered_map<CommandID, command::Command> ProgramMap;
typedef std::unordered_map<string, Menu> MenuMap;
typedef std::unordered_map<string, MenuBar> MenuBarMap;

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

void makeRecentFiles(PopupMenu* menu) {
}

}  // namespace

class ProgramInstance::Impl {
 public:
  Impl(Program* p)
      : program_(p),
        programMap_(makeProgramMap(*p)),
        menuMap_(makeMenuMap(*p)),
        menuBarMap_(makeMenuBarMap(*p)) {
  }

  const MenuBar& menuBar() const {
    return menuBarMap_.at(program_->menuBarName());
  }

  void addSubmenu(PopupMenu* popup, const MenuEntry& menuEntry) {
    PopupMenu submenu;
    string subname = addMenu(&submenu, menuEntry.submenu());
    popup->addSubMenu(subname, submenu);
  }

  void addCommands(PopupMenu* popup, const MenuEntry& menuEntry) {
    for (auto& command: menuEntry.command()) {
      if (command)
        popup->addCommandItem(&applicationCommandManager, command);
      else
        popup->addSeparator();
    }
  }

  void addMenuEntry(PopupMenu* popup, const MenuEntry& menuEntry) {
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

  string addMenu(PopupMenu* popup, const string& name) {
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

  Program* program_;
  ProgramMap programMap_;
  const MenuCollection menuCollection;
  const MenuMap menuMap_;
  const MenuBarMap menuBarMap_;
  ApplicationCommandManager applicationCommandManager;
};

ProgramInstance::ProgramInstance(Program* p) : impl_(new Impl(p)) {}
ProgramInstance::~ProgramInstance() {}

void ProgramInstance::getAllCommands(juce::Array<CommandID>& commands) {
  for (auto& mapEntry: impl_->programMap_)
    commands.add(mapEntry.first);
}

void ProgramInstance::getCommandInfo(CommandID command,
                                     ApplicationCommandInfo& info) {
  try {
    const Command& command = impl_->programMap_.at(info.commandID);
    const Description& desc = command.desc();
    int flags = command.flags();
    if (hasProperty(*impl_->program_, command.disabled()))
      flags |= ApplicationCommandInfo::isDisabled;
    if (hasProperty(*impl_->program_, command.ticked()))
      flags |= ApplicationCommandInfo::isTicked;

    info.setInfo(desc.name(), desc.full(0), command.category(), flags);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "getCommandInfo out of range " << info.commandID;
  }
}

bool ProgramInstance::perform(const InvocationInfo& info) {
  try {
    const Command& command = impl_->programMap_.at(info.commandID);
    return impl_->program_->perform(info, command);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Tried to invoke out of range command " << info.commandID;
    return false;
  }
}

StringArray ProgramInstance::getMenuBarNames() {
  StringArray names;
  try {
    for (auto& menu: impl_->menuBar().menu())
      names.add(menu);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Couldn't get menu bar";
  }
  return names;
}

ApplicationCommandManager* ProgramInstance::applicationCommandManager() {
  return &impl_->applicationCommandManager;
}

PopupMenu ProgramInstance::getMenuForIndex(int menuIndex,
                                           const String&) {
  PopupMenu menu;
  try {
    const MenuBar& mb = impl_->menuBar();
    if (menuIndex >= mb.menu_size())
      LOG(DFATAL) << "out of range: " << menuIndex << " > " << mb.menu_size();
    else
      impl_->addMenu(&menu, mb.menu(menuIndex));
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "Couldn't get menubar " << menuIndex;
  }

  return menu;
}

}  // namespace app
}  // namespace rec
