#include "rec/command/CommandMap.h"

namespace rec {
namespace command {

void CommandMap::operator()(const CommandMapProto& commands) {
  toCommand_.clear();
  toKeys_.clear();
  for (int i = 0; i < commands.entry_size(); ++i) {
    const CommandMapEntry& entry = commands.entry(i);
    Command command = entry.command();
    for (int j = 0; j < entry.key_size(); ++j) {
      const Key& key = entry.key(j);
      toCommand_[key] = command;
      toKeys_.insert(std::make_pair(command, key));
    }
  }
}

const CommandMapProto CommandMap::getProto() const {
  CommandMapProto commands;
  CommandMapEntry* entry = NULL;
  CommandToKeys::const_iterator i;
  for (i = toKeys_.begin(); i != toKeys_.end(); ++i) {
    if (!entry || entry->command() != i->first) {
      entry = commands.add_entry();
      entry->set_command(i->first);
    }
    entry->add_key(i->second);
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

const vector<CommandMap::Key> CommandMap::getKeys(Command c) const {
  typedef CommandToKeys::const_iterator const_iterator;
  typedef std::pair<const_iterator, const_iterator> IteratorPair;
  IteratorPair range(toKeys_.equal_range(c));

  vector<CommandMap::Key> keys;
  for (const_iterator i = range.first; i != range.second; ++i)
    keys.push_back(i->second);

  return keys;
}

}  // namespace command
}  // namespace rec

