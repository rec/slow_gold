#include <unordered_set>

#include "rec/program/MakeMaps.h"

#include "rec/program/Program.h"

namespace rec {
namespace program {

CommandMap makeCommandMap(const Program& program) {
  CommandMap commandMap;
  auto commands = program.commands().command();

  for (auto& command: commands) {
    CommandID id = command.id();
    commandMap[id] = command;
    if (command.has_index()) {
      for (int i = 0; i < command.index(); ++i)
        commandMap[id + i] = command;
    }
  }

  auto map = program.keypresses().map();
  for (auto& entry: map.entry()) {
    CommandID id = entry.id();
    if (entry.has_index())
      id += entry.index() - CommandIDs::FIRST;
    try {
      *commandMap.at(id).mutable_keypress() = entry.key();
    } catch (const std::out_of_range&) {
      LOG(ERROR) << "Out of range keypress command." << program.commandName(id);
    }
  }

  return commandMap;
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
  auto menus = program.menus();
  for (auto& menu: menus.menu())
    menuMap[menu.description().name()] = menu;

  for (auto& i: menuMap)
    fixExtends(&i.second, &menuMap);
  return menuMap;
}

MenuBarMap makeMenuBarMap(const Program& program) {
  MenuBarMap menuBarMap;
  auto menuBars = program.menuCollection().menu_bar();
  for (auto& menuBar: menuBars)
    menuBarMap[menuBar.description().name()] = menuBar;
  return menuBarMap;
}

}  // namespace program
}  // namespace rec
