#include "rec/slow/commands/SlowProgram.h"
#include "rec/command/CommandRecord.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/slow/Instance.h"
#include "rec/slow/callbacks/Callbacks.h"

namespace rec {
namespace slow {

command::Commands SlowProgram::commands() const {
  command::Commands commands;
  return commands;
}

command::Commands SlowProgram::keypresses() const {
  command::Commands keypresses;
  return keypresses;
}

program::Menus SlowProgram::menus() const {
  program::Menus menus;
  return menus;
}

program::MenuCollection SlowProgram::menuCollection() const {
  program::MenuCollection menuCollection;
  return menuCollection;
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


}  // namespace slow
}  // namespace rec
