#include "rec/command/Command.h"
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

}  // namespace command
}  // namespace rec
