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

}  // namespace

struct ProgramInstance::Impl {
  Impl(Program* p)
      : program(p),
        programMap(makeProgramMap(*p)),
        menuMap(makeMenuMap(*p)),
        menuBarMap(makeMenuBarMap(*p)) {
  }

  const MenuBar& menuBar() const {
    return menuBarMap.at(program->menuBarName());
  }

  string addMenu(PopupMenu* popup, const string& name) {
    string result;
    try {
      const Menu& menu = menuMap.at(name);
      for (auto& menuEntry: menu.entry()) {
        if (menuEntry.has_command() and menuEntry.has_submenu())
          LOG(DFATAL) << "Menu has command and submenu: " << menu.DebugString();
        if (menuEntry.has_command()) {
          popup->addCommandItem(&applicationCommandManager, menuEntry.command());
        } else if (menuEntry.has_submenu()) {
          PopupMenu submenu;
          string subname = addMenu(&submenu, menuEntry.submenu());
          popup->addSubMenu(subname, submenu);
        } else {
          popup->addSeparator();
        }
      }
      return menu.description().menu(0);
    } catch (const std::out_of_range&) {
      LOG(DFATAL) << "Couldn't get menu " << name;
      return "";
    }
  }

  Program* program;
  ProgramMap programMap;
  const MenuCollection menuCollection;
  const MenuMap menuMap;
  const MenuBarMap menuBarMap;
  ApplicationCommandManager applicationCommandManager;
};

ProgramInstance::ProgramInstance(Program* p) : impl_(new Impl(p)) {}
ProgramInstance::~ProgramInstance() {}

void ProgramInstance::getAllCommands(juce::Array<CommandID>& commands) {
  for (auto& mapEntry: impl_->programMap)
    commands.add(mapEntry.first);
}

void ProgramInstance::getCommandInfo(CommandID command,
                                     ApplicationCommandInfo& info) {
  try {
    const Command& command = impl_->programMap.at(info.commandID);
    const Description& desc = command.desc();
    int flags = command.flags();
    if (hasProperty(*impl_->program, command.disabled()))
      flags |= ApplicationCommandInfo::isDisabled;
    if (hasProperty(*impl_->program, command.ticked()))
      flags |= ApplicationCommandInfo::isTicked;

    info.setInfo(desc.name(), desc.full(0), command.category(), flags);
  } catch (const std::out_of_range&) {
    LOG(DFATAL) << "getCommandInfo out of range " << info.commandID;
  }
}

bool ProgramInstance::perform(const InvocationInfo& info) {
  try {
	  return impl_->program->perform(info, impl_->programMap.at(info.commandID));
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
