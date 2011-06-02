#include "rec/command/CommandMap.h"

namespace rec {
namespace command {

void CommandMap::initialize(const CommandMapProto& commands) {
  toCommand_.clear();
  for (int i = 0; i < commands.entry_size(); ++i) {
    const CommandMapEntry& entry = commands.entry(i);
    toCommand_[entry.key()] = entry.command();
    toKey_[entry.command()] = entry.key();
  }
}

const CommandMapProto CommandMap::getProto() const {
  CommandMapProto commands;
  for (KeyToCommand::const_iterator i = toCommand_.begin();
       i != toCommand_.end(); ++i) {
    CommandMapEntry* entry = commands.add_entry();
    entry->set_key(i->first);
    entry->set_command(i->second);
  }

  return commands;
}


bool CommandMap::invoke(const Key& key, ApplicationCommandManager* acm,
                        bool async) const {
  if (CommandID id = getCommand(key))
    return acm->invokeDirectly(id, async);
  else
    return false;
}

command::Command::Type CommandMap::getCommand(const string& key) const {
  KeyToCommand::const_iterator i = toCommand_.find(key);
  return (i == toCommand_.end()) ? command::Command::NONE : i->second;
}

const CommandMap::Key CommandMap::getKey(Command c) const {
  CommandToKey::const_iterator i = toKey_.find(c);
  return (i == toKey_.end()) ? "" : i->second;
}

}  // namespace command
}  // namespace rec

