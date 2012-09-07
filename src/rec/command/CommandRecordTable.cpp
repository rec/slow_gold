#include "rec/command/CommandRecordTable.h"

#include "rec/command/Access.pb.h"
#include "rec/command/CommandDatabase.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/data/Data.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/util/STL.h"

namespace rec {
namespace command {

CommandRecordTable::~CommandRecordTable() {
  stl::deleteMapPointers(&table_);
}

void CommandRecordTable::writeTable() const {
#ifdef DEBUG
  File out("/tmp/records.txt");
  out.deleteFile();

  Commands commands;
  for (const_iterator i = table_.begin(); i != table_.end(); ++i)
    commands.add_command()->CopyFrom(*i->second->command_);

  String res = str(commands.DebugString());
  juce::FileOutputStream(out).writeText(res, false, false);
#endif
}

CommandRecord* CommandRecordTable::find(CommandID id, bool create) {
  CHECK(id != CommandIDEncoder::toCommandID(Command::JUMP, 10) || !create);
  CommandRecordTable::iterator i = table_.find(id);
  if (i != table_.end())
    return i->second;

  if (!create)
    return NULL;

  ptr<CommandRecord> rec(new CommandRecord(id));
  table_.insert(i, std::make_pair(id, rec.get()));
  return rec.transfer();
}

const Commands CommandRecordTable::getCommands() const {
  Commands commands;
  CommandRecordTable::const_iterator i;
  for (i = table_.begin(); i != table_.end(); ++i) {
    if (i->second->command_)
      commands.add_command()->CopyFrom(*(i->second->command_));
  }
  return commands;
}

string commandName(CommandID id) {
  return CommandIDEncoder::commandIDName(id);
}

const CommandID JUMP_TO_FIRST =
  CommandIDEncoder::toCommandID(CommandIDEncoder::FIRST, Command::JUMP);

}  // namespace command
}  // namespace rec
