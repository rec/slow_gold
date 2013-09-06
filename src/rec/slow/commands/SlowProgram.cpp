#include "rec/slow/commands/SlowProgram.h"
#include "rec/slow/Instance.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Undo.h"

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

  if (name == "cant_copy")
    return not canCopy();

  if (name == "cant_cut")
    return not canCut();

  if (name == "cant_paste")
    return not canPaste();

  if (name == "cant_redo")
    return not canUndo();

  if (name == "cant_undo")
    return not canRedo();

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
