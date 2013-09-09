#include "rec/slow/commands/SlowProgram.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/slow/Instance.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommandData.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/Binary.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace slow {

command::Commands SlowProgram::commands() const {
  return makeCommand();
}

command::KeyStrokeCommandMapProto SlowProgram::keypresses() const {
  return makeKeyBindings();
}

program::Menus SlowProgram::menus() const {
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
  slow::addSlowCallbacks(&crt, true);
  for (auto& i: *crt.table())
    addCallback(i.first, std::move(i.second->callback_));
}

VirtualFile SlowProgram::getCurrentFile() const {
  return instance_->file();
}

void SlowProgram::beforeCommand(CommandID id) {
	if (id != SlowCommand::ABOUT_THIS_PROGRAM && instance_->window_)
    thread::callAsync(instance_->window_, &app::Window::stopAboutWindow);
}

const int MARGIN = 10;

string SlowProgram::commandName(CommandID id) const {
  return rec::slow::commandName(id);
}

string commandName(CommandID id) {
  bool isCompound = id > SlowCommand::BANK_SIZE - MARGIN;
  int mod;
  if (isCompound) {
    mod = (id + MARGIN) % SlowCommand::BANK_SIZE - MARGIN;
    id -= mod;
  }
  string name = SlowCommand_Type_Name(static_cast<SlowCommand::Type>(id));
  if (isCompound)
    name += str(":" + String(mod));
  return name;
}

}  // namespace slow
}  // namespace rec
