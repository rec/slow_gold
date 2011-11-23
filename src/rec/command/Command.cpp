#include "rec/audio/stretch/Stretch.h"
#include "rec/command/Access.pb.h"
#include "rec/command/CommandDataSetter.h"
#include "rec/command/data/CommandData.h"
#include "rec/data/Data.h"
#include "rec/slow/Position.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/Defaulter.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace command {

const Commands fromCommandTable(const CommandTable& table) {
  Commands commands;
  for (CommandTable::const_iterator i = table.begin(); i != table.end(); ++i)
    commands.add_command()->CopyFrom(*(i->second));
  return commands;
}

const CommandTable toCommandTable(const Commands& commands) {
  CommandTable table;
  for (int i = 0; i < commands.command_size(); ++i) {
    const Command& c = commands.command(i);
    table[slow::Position::toCommandID(c)] = new Command(c);
  }
  return table;
}

CommandContext::CommandContext(Listener<None>* listener) {
  Access access = data::get<Access>();

  insertSingle(&commands_);
  insertRepeated(&commands_);
  insertSetters(this, listener);
  mergeKeyPresses(&commands_, access);
  mergeDescriptions(&commands_, access);
  removeEmpties(&commands_);
}

CommandContext::~CommandContext() {
  stl::deleteMapPointers(&commands_);
  stl::deleteMapPointers(&setters_);
  stl::deleteMapPointers(&callbacks_);  // TODO: this causes a crash on exit.
}

}  // namespace command
}  // namespace rec
