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

CommandRecord* CommandRecordTable::find(CommandID id, bool create) {
  Lock l(lock_);
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
  Lock l(lock_);
  Commands commands;
  CommandRecordTable::const_iterator i;
  for (i = table_.begin(); i != table_.end(); ++i) {
    if (i->second->command_)
      commands.add_command()->CopyFrom(*(i->second->command_));
  }
  return commands;
}

}  // namespace command
}  // namespace rec
