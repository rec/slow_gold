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
  Table::iterator i = table_.find(id);
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
  Table::const_iterator i;
  for (i = table_.begin(); i != table_.end(); ++i) {
    if (i->second->command_)
      commands.add_command()->CopyFrom(*(i->second->command_));
  }
  return commands;
}

void CommandRecordTable::getAllCommands(juce::Array<CommandID>* commands) {
  commands->clear();
  Table::const_iterator i;
  for (i = table_.begin(); i != table_.end(); ++i) {
    if (i->second->callback_)
      commands->add(i->first);
  }
}

void CommandRecordTable::fillCommandInfo() {
  Table::const_iterator i;
  for (i = table_.begin(); i != table_.end(); ++i) {
    CommandID id = i->first;
    CommandRecord* cr = i->second;
    if (!cr->callback_)
      LOG(DFATAL) << "Empty callback " << CommandIDEncoder::commandIDName(id);

    const Description& desc = cr->command_->desc();
    String name = Trans(desc.full(0));
    String category = str(cr->command_->category());
    bool hasInfo = desc.menu_size() && name.length();

    if (hasInfo) {
      int flags = 0;
      if (category == "" || category == "(None)") {
        DCHECK_NE(category, "");
        flags += ApplicationCommandInfo::hiddenFromKeyEditor;
      }

      cr->info_.setInfo(Trans(desc.menu(0)), name, category, flags);
    } else {
      LOG(DFATAL) << "No command " << CommandIDEncoder::commandIDName(id)
                 << ", " << desc.menu_size()
                 << ", " << name.length()
                 << cr->command_->ShortDebugString();
    }
  }
}

void CommandRecordTable::addCallback(CommandID id, Callback* cb) {
  CommandRecord* cr = find(id, true);
  if (cr->callback_)
    LOG(DFATAL) << "Repeated callback " << CommandIDEncoder::commandIDName(id);
  cr->callback_.reset(cb);
}

}  // namespace command
}  // namespace rec
