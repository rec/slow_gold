#include "rec/command/Command.h"

#include "rec/command/Access.pb.h"
#include "rec/command/CommandDatabase.h"
#include "rec/data/Data.h"
#include "rec/slow/Position.h"
#include "rec/util/STL.h"

namespace rec {
namespace command {

const CommandRecordTable makeCommandRecordTable(Listener<None>* listener) {
  CommandRecordTable commands;

  Access access = data::get<Access>();

  insertSingle(&commands);
  insertRepeated(&commands);
  insertSetters(&commands, listener);
  mergeKeyPresses(&commands, access);
  mergeDescriptions(&commands, access);
  removeEmpties(&commands);

  return commands;
}

CommandRecord* find(CommandRecordTable* table, CommandID id) {
  CommandRecordTable::iterator i = table->find(id);
  if (i != table->end())
    return i->second;
  ptr<CommandRecord> rec(new CommandRecord);
  table->insert(i, std::make_pair(id, rec.get()));
  return rec.transfer();
}

#if 0

const Commands fromCommandTable(const CommandTable&);

const Commands fromCommandTable(const CommandTable& table) {
  Commands commands;
  for (CommandTable::const_iterator i = table.begin(); i != table.end(); ++i)
    commands.add_command()->CopyFrom(*(i->second));
  return commands;
}

const CommandTable toCommandTable(const Commands&);

const CommandTable toCommandTable(const Commands& commands) {
  CommandTable table;
  for (int i = 0; i < commands.command_size(); ++i) {
    const Command& c = commands.command(i);
    table[slow::Position::toCommandID(c)] = new Command(c);
  }
  return table;
}

#endif

}  // namespace command
}  // namespace rec
