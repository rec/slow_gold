#include "rec/command/Command.h"

#include "rec/command/Access.pb.h"
#include "rec/command/CommandDatabase.h"
#include "rec/data/Data.h"
#include "rec/slow/Position.h"
#include "rec/util/STL.h"

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
  stl::deleteMapPointers(&callbacks_);
}

}  // namespace command
}  // namespace rec
