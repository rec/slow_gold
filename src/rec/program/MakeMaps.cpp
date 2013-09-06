#include "rec/program/MakeMaps.h"
#include "rec/program/Program.h"

namespace rec {
namespace program {

ProgramMap makeProgramMap(const Program& program) {
  ProgramMap programMap;
  for (auto& command: program.commands().command()) {
    CommandID id = command.command();
    programMap[id] = command;
    for (int i = command.start_index(); i < command.index(); ++i)
      programMap[id + i] = command;
  }

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

}  // namespace program
}  // namespace rec
