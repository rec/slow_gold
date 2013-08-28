#include "rec/command/CommandRecordTable.h"

#include "rec/command/CommandRecord.h"
#include "rec/data/Data.h"
#include "rec/util/STL.h"

namespace rec {
namespace command {

CommandRecordTable::~CommandRecordTable() {
  stl::deleteMapPointers(&table_);
}

CommandRecord* CommandRecordTable::locate(ID id, bool mustExist,
                                          bool mustCreate) {
  Lock l(lock_);
  Table::iterator i = table_.find(id);
  if (i != table_.end()) {
    if (mustCreate)
      LOG(DFATAL) << id << " already exists.";
    return i->second;
  }
  if (mustExist)
    return nullptr;

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

void CommandRecordTable::getAllCommands(juce::Array<CommandID>* cmds) const {
  Lock l(lock_);
  cmds->clear();
  Table::const_iterator i;
  for (i = table_.begin(); i != table_.end(); ++i) {
    if (i->second->callback_)
      cmds->add(i->first);
  }
}

void CommandRecordTable::addCallback(ID id, Callback* cb) {
  Lock l(lock_);
  create(id)->callback_.reset(cb);
}

void CommandRecordTable::fillAllCommands() {
  Lock l(lock_);
  for (Table::iterator i = table_.begin(); i != table_.end(); ++i)
    i->second->fillInfo();
}

}  // namespace command
}  // namespace rec
