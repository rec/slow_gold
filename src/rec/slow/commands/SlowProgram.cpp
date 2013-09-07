#include "rec/slow/commands/SlowProgram.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/slow/Instance.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommandData.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/Binary.h"

namespace rec {
namespace slow {

command::Commands SlowProgram::commands() const {
  LOG(INFO) << "SlowProgram::commands()";
  return makeCommand();
}

command::KeyStrokeCommandMapProto SlowProgram::keypresses() const {
  LOG(INFO) << "SlowProgram::keypresses()";
  return makeKeyBindings();
}

program::Menus SlowProgram::menus() const {
  LOG(INFO) << "SlowProgram::menus()";
  SlowMenus slowMenus = BINARY_PROTO(SlowMenus, SlowMenus);
  program::Menus menus;
  for (auto& slowMenu: slowMenus.menu()) {
    program::Menu* menu = menus.add_menu();
    menu->mutable_description()->CopyFrom(slowMenu.description());
    if (slowMenu.has_extends())
      menu->set_extends(slowMenu.extends());
    for (auto& slowEntry: slowMenu.entry()) {
      program::MenuEntry* menuEntry = menu->add_entry();
      for (auto& command: slowEntry.command())
        menuEntry->add_command(command);
      if (slowEntry.has_submenu())
        menuEntry->set_submenu(slowEntry.submenu());
      if (slowEntry.has_is_recent_files_menu())
        menuEntry->set_is_recent_files_menu(slowEntry.is_recent_files_menu());
      if (slowEntry.has_callout_function())
        menuEntry->set_callout_function(slowEntry.callout_function());
    }
  }

  return menus;
}

program::MenuCollection SlowProgram::menuCollection() const {
  return BINARY_PROTO(SlowMenuCollection, program::MenuCollection);
}

string SlowProgram::menuBarName() const {
  return "";
}

bool SlowProgram::hasProperty(const string& name) const {
  if (name == "empty")
    return instance_->empty();
  return ProgramBase::hasProperty(name);
}

string SlowProgram::makeMenuName(const command::Command&, CommandID) const {
  return "";
}

const gui::RecentFilesStrategy& SlowProgram::recentFilesStrategy() const {
  return gui::getMusicRecentFilesStrategy();
}


void SlowProgram::registerAllCallbacks() {
  command::CommandRecordTable crt;
  slow::addSlowCallbacks(&crt);
  for (auto& i: *crt.table())
    addCallback(i.first, std::move(i.second->callback_));
}

VirtualFile SlowProgram::getCurrentFile() const {
  return instance_->file();
}

string SlowProgram::commandName(CommandID id) const {
  return SlowCommand_Type_Name(static_cast<SlowCommand::Type>(id));
}

}  // namespace slow
}  // namespace rec
