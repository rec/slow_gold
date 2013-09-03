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

Commands makeCommand() {
  SlowCommands slowCommands = BINARY_PROTO(SlowCommands_def, SlowCommands);

  Commands commands;
  for (auto& slowCommand: slowCommands.slow_command()) {
    Command* command = commands.add_command();
    *command = slowCommand.command();
    command->set_command(static_cast<slow::SlowCommand::Type>(slowCommand.type()));
  }
  return commands;
}

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

CommandData* createSlowCommandData(Instance* i) { return new SlowCommandData(i); }

app::Menus createMenus() {
  app::Menus menus;
  SlowMenus slowMenus = BINARY_PROTO(SlowMenus_def, SlowMenus);

  for (auto& menu: slowMenus.menu()) {
    app::Menu* appMenu = menus.add_menu();
    *appMenu->mutable_description() = menu.description();
    appMenu->set_extends(menu.extends());
    for (auto& menuEntry: menu.entry()) {
      app::MenuEntry* appMenuEntry = appMenu->add_entry();
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

}  // namespace slow
}  // namespace rec
