#include <unordered_set>

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

typedef std::unordered_set<string> StringSet;

static void fixExtends(Menu* menu, MenuMap* map, StringSet* seen = nullptr) {
  if (menu->has_extends()) {
    const string& extends = menu->extends();
    if (seen and seen->count(extends)) {
      LOG(DFATAL) << "Circular reference in menu " << extends;
      return;
    }
    try {
      Menu* extendedMenu = &map->at(extends);
      unique_ptr<StringSet> seenDeleter;
      if (not seen) {
        seen = new StringSet;
        seenDeleter.reset(seen);
      }
      seen->insert(extends);
      fixExtends(extendedMenu, map, seen);

      Menu mergedMenu;
      auto mergedEntry = mergedMenu.mutable_entry();
      auto menuEntry = menu->mutable_entry();
      mergedEntry->CopyFrom(extendedMenu->entry());
      mergedEntry->MergeFrom(*menuEntry);
      mergedEntry->Swap(menuEntry);
      menu->clear_extends();
    } catch (const std::out_of_range&) {
      LOG(DFATAL) << "Couldn't resolve extends: " << extends;
    }
  }
}

MenuMap makeMenuMap(const Program& program) {
  MenuMap menuMap;
  for (auto& menu: program.menus().menu())
    menuMap[menu.description().name()] = menu;

  for (auto& i: menuMap)
    fixExtends(&i.second, &menuMap);
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
