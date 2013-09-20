#include <unordered_set>

#include "rec/program/MakeMaps.h"
#include "rec/command/Command.pb.h"
#include "rec/program/Program.h"
#include "rec/util/BinaryMacros.h"
#include "rec/util/thread/Looper.h"

using namespace rec::command;

namespace rec {
namespace program {

namespace {

template <typename Type>
CommandID fixId(const Program& program, Type* item) {
  if (not item->has_id())
    item->set_id(program.nameToId(item->id_string()));
  return item->id();
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

}  // namespace

CommandMap makeCommandMap(const Program& program) {
  CommandMap commandMap;
  command::Commands commands = BINARY_PROTO_MERGED(Commands, command::Commands);

  for (auto& command: *commands.mutable_command()) {
    CommandID id = fixId(program, &command);
    commandMap[id] = command;
    if (command.has_index()) {
      for (int i = 0; i < command.index(); ++i)
        commandMap[id + i] = command;
    }
  }

  return commandMap;
}

command::CommandMapProto makeKeyMap(const Program& program) {
  CommandMapProto keys = BINARY_PROTO(KeyStrokeMap, CommandMapProto);
  for (auto& entry: *keys.mutable_entry())
    fixId(program, &entry);
  return keys;
}

void mergeKeysIntoCommands(const CommandMapProto& keys, CommandMap* map) {
  for (auto& entry: keys.entry()) {
    CommandID id = entry.id();
    if (entry.has_index())
      id += entry.index() - CommandIDs::FIRST;
    try {
      auto& commandEntry = map->at(id);
      DCHECK(not commandEntry.keypress_size());
      *commandEntry.mutable_keypress() = entry.key();
    } catch (const std::out_of_range&) {
      LOG(ERROR) << "Out of range keypress command." << id;
    }
  }
}

MenuMap makeMenuMap(const Program& program) {
  MenuMap menuMap;
  Menus menus = BINARY_PROTO(Menus, Menus);
  for (auto& menu: *menus.mutable_menu()) {
    for (auto& entry: *menu.mutable_entry()) {
      for (auto& id_string: entry.id_string())
        entry.add_id(program.nameToId(id_string));
    }
    menuMap[menu.description().name()] = menu;
  }

  for (auto& i: menuMap)
    fixExtends(&i.second, &menuMap);
  return menuMap;
}

MenuBarMap makeMenuBarMap(const Program& program) {
  MenuBarMap menuBarMap;
  MenuCollection menuCollection = BINARY_PROTO(MenuCollection, MenuCollection);
  for (auto& menuBar: menuCollection.menu_bar())
    menuBarMap[menuBar.description().name()] = menuBar;
  return menuBarMap;
}

ThreadMap makeThreadMap(const Program& program) {
  ThreadMap threadMap;
  ThreadProtos threads = BINARY_PROTO(Threads, ThreadProtos);
  for (auto& thread: threads.thread()) {
    auto f = program.threadFunction(thread.name());
    unique_ptr<Thread> t(new thread::Looper(thread.name(), f, thread.period()));
    t->setPriority(thread.priority());
    threadMap[thread.name()] = std::move(t);
  }
  return threadMap;
}

LayoutMap makeLayoutMap(const Program& program) {
  LayoutMap layoutMap;
  gui::Layouts layouts = BINARY_PROTO_MERGED(Layout, gui::Layouts);
  for (auto& layout: layouts.layout())
    layoutMap[layout.name()] = layout;
  return layoutMap;
}

}  // namespace program
}  // namespace rec
