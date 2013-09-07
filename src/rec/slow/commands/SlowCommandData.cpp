#include "rec/slow/commands/SlowCommandData.h"

#include "rec/command/CommandData.h"
#include "rec/slow/Menus.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/Binary.h"

namespace rec {
namespace slow {

using namespace rec::command;

namespace {

class SlowCommandData : public CommandData {
 public:
  explicit SlowCommandData(Instance* i)
      : update_(i->menus_.get()),
        allCommands_(makeCommand()) {
  }
  const Commands& allCommands() const { return allCommands_; }

  virtual void addCallbacks(command::CallbackTable* table) const {
    addSlowCallbacks(table);
  }

  Listener<None>* getMenuUpdateListener() const { return update_; }

 private:
 	Listener<None>* update_;
  const command::Commands allCommands_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowCommandData);
};

}  // namespace

Commands makeCommand() {
  SlowCommands slowCommands = BINARY_PROTO(SlowCommands, SlowCommands);

  Commands commands;
  for (auto& slowCommand: slowCommands.slow_command()) {
    Command* command = commands.add_command();
    *command = slowCommand.command();
    command->set_command(static_cast<slow::SlowCommand::Type>(slowCommand.type()));
  }
  return commands;
}

CommandData* createSlowCommandData(Instance* i) { return new SlowCommandData(i); }

program::Menus createMenus() {
  program::Menus menus;
  SlowMenus slowMenus = BINARY_PROTO(SlowMenus, SlowMenus);

  for (auto& menu: slowMenus.menu()) {
    program::Menu* appMenu = menus.add_menu();
    *appMenu->mutable_description() = menu.description();
    appMenu->set_extends(menu.extends());
    for (auto& menuEntry: menu.entry()) {
      program::MenuEntry* appMenuEntry = appMenu->add_entry();
      for (auto& command: menuEntry.command())
        appMenuEntry->add_command(command);
      if (menuEntry.has_submenu())
        appMenuEntry->set_submenu(menuEntry.submenu());
      appMenuEntry->set_is_recent_files_menu(menuEntry.is_recent_files_menu());
      if (menuEntry.has_callout_function())
        appMenuEntry->set_callout_function(menuEntry.callout_function());
    }
  }

  return menus;
}

KeyStrokeCommandMapProto makeKeyBindings() {
  slow::SlowCommandMapProto slowMaps =
    BINARY_PROTO(SlowKeyStrokeMap, slow::SlowCommandMapProto);

  KeyStrokeCommandMapProto bindings;
  auto map = bindings.mutable_map();
  for (auto& slowEntry: slowMaps.slow_entry()) {
    auto entry = map->add_entry();
    *entry = slowEntry.entry();
    entry->set_command(slowEntry.command());
  }
  return bindings;
}

}  // namespace slow
}  // namespace rec
