#include "rec/command/Command.h"

#include "rec/command/Access.pb.h"
#include "rec/command/CommandDatabase.h"
#include "rec/data/Data.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/util/STL.h"

namespace rec {
namespace command {

void addCommandDatabase(CommandRecordTable* table, Listener<None>* listener) {
  Access access = data::get<Access>();

  insertSingle(table);
  insertRepeated(table);
  insertSetters(table, listener);
  mergeKeyPresses(table, access);
  mergeDescriptions(table, access);
  removeEmpties(table);
}

CommandRecord* find(CommandRecordTable* table, CommandID id, bool create) {
  DCHECK_NE(id, CommandIDEncoder::toCommandID(Command::JUMP, 10));
  CommandRecordTable::iterator i = table->find(id);
  if (i != table->end())
    return i->second;

  if (!create)
    return NULL;

  ptr<CommandRecord> rec(new CommandRecord);
  table->insert(i, std::make_pair(id, rec.get()));
  return rec.transfer();
}

const Commands fromCommandTable(const CommandRecordTable& table) {
  Commands commands;
  CommandRecordTable::const_iterator i;
  for (i = table.begin(); i != table.end(); ++i) {
    if (i->second->command_)
      commands.add_command()->CopyFrom(*(i->second->command_));
  }
  return commands;
}

string commandName(CommandID id) {
  return CommandIDEncoder::commandIDName(id);
}

}  // namespace command
}  // namespace rec
