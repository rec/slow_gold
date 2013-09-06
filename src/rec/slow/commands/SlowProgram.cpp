#include "rec/slow/commands/SlowProgram.h"

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
  return false;
}

string SlowProgram::makeMenuName(const command::Command&, CommandID) const {
  return "";
}

const gui::RecentFilesStrategy& SlowProgram::recentFilesStrategy() const {
  return gui::getMusicRecentFilesStrategy();
}


void SlowProgram::registerAllCallbacks() {
}

}  // namespace slow
}  // namespace rec
