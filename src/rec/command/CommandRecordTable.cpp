#include "rec/command/CommandRecordTable.h"

#include "rec/command/Access.pb.h"
#include "rec/command/FillCommandRecordTable.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/data/Data.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/util/STL.h"

namespace rec {
namespace command {

CommandRecordTable::~CommandRecordTable() {
  stl::deleteMapPointers(&table_);
}

CommandRecord* CommandRecordTable::find(CommandID id) {
  Lock l(lock_);
  Table::iterator i = table_.find(id);
  return (i != table_.end()) ? i->second : NULL;
}

CommandRecord* CommandRecordTable::create(CommandID id, bool allowDupes) {
  Lock l(lock_);
  Table::iterator i = table_.find(id);
  if (i != table_.end()) {
    if (!allowDupes)
      LOG(DFATAL) << CommandIDEncoder::commandIDName(id) << " already exists.";
    return i->second;
  }

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
  create(id)->callback_.reset(cb);
}

bool CommandRecordTable::perform(CommandID id) {
  Lock l(lock_);
  CommandRecord* cr = find(id);
  bool success = false;
  if (!cr)
    LOG(DFATAL) << "No record for " << CommandIDEncoder::commandIDName(id);
  else if (!cr->callback_)
    LOG(DFATAL) << "No callback for " << CommandIDEncoder::commandIDName(id);
  else
    success = true;

  if (success)
    (*(cr->callback_))();

  return success;
}

void CommandRecordTable::fillCommandInfo(CommandID id, const String& name,
                                         int flags, Enable enable) {
  Lock l(lock_);
  CommandRecord* cr = find(id);
  if (!cr) {
    LOG(DFATAL) << "no info for " << CommandIDEncoder::commandIDName(id);
    return;
  }
  ApplicationCommandInfo* info = cr->getInfo();

  if (name.length())
    info->shortName = name;
  else if (cr->setter_)
    info->shortName = str(cr->setter_->menuName());

  if (!info->shortName.length()) {
    LOG(ERROR) << "No name for " << CommandIDEncoder::commandIDName(id);
    info->shortName = "(error)";
  }
  if (flags >= 0)
    info->flags = flags;

  info->setActive(enable == ENABLE);
}

void CommandRecordTable::fillAllCommands() {
  for (Table::iterator i = table_.begin(); i != table_.end(); ++i)
    i->second->fillInfo();
}

}  // namespace command
}  // namespace rec
