#include "rec/command/Command.h"
#include "rec/command/CommandDatabase.h"
#include "rec/slow/Position.h"

namespace rec {
namespace command {

static CommandDatabase* commandDatabase() {
  static CommandDatabase d;
  return &d;
}

const CommandContext getCommandContext() {
  return commandDatabase()->context();
}

void recalculate() {
  commandDatabase()->recalculate();
}

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
