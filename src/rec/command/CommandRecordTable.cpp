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

CommandRecord* CommandRecordTable::findOrCreate(CommandID id) {
  Lock l(lock_);
  Table::iterator i = table_.find(id);
  return (i != table_.end()) ? i->second : NULL;
}

CommandRecord* CommandRecordTable::findDontCreate(CommandID id) {
  Lock l(lock_);
  Table::iterator i = table_.find(id);
  if (i != table_.end())
    return i->second;

  ptr<CommandRecord> rec(new CommandRecord(id));
  table_.insert(i, std::make_pair(id, rec.get()));
  return rec.transfer();
}

const Commands CommandRecordTable::getCommands() const {
  Lock l(lock_);
  Commands commands;
  Table::const_iterator i;
  for (i = table_.begin(); i != table_.end(); ++i) {
    if (i->second->command_)
      commands.add_command()->CopyFrom(*(i->second->command_));
  }
  return commands;
}

void CommandRecordTable::getAllCommands(juce::Array<CommandID>* commands) {
  Lock l(lock_);
  commands->clear();
  Table::const_iterator i;
  for (i = table_.begin(); i != table_.end(); ++i) {
    if (i->second->callback_)
      commands->add(i->first);
  }
}

void CommandRecordTable::addCallback(CommandID id, Callback* cb) {
  Lock l(lock_);

  CommandRecord* cr = findOrCreate(id);
  if (cr->callback_)
    LOG(DFATAL) << "Repeated callback " << CommandIDEncoder::commandIDName(id);
  cr->callback_.reset(cb);
}

}  // namespace command
}  // namespace rec
