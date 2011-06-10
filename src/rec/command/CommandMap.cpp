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

void CommandMap::removeMessage(Command c, int keyIndex) {
  typedef CommandToKeys::iterator iterator;
  iterator i = toKeys_.lower_bound(c);
  for (int j = 0; j < keyIndex && i != toKeys_.end(); ++i, ++j);
  if (i == toKeys_.end()) {
    LOG(ERROR) << "Couldn't remove message";
    return;
  }

  toCommand_.erase(i->second);
  toKeys_.erase(i);
}

void CommandMap::removeKey(const Key& key) {
  typedef CommandToKeys::iterator iterator;
  if (Command c = getCommand(key)) {
    toCommand_.erase(key);
    iterator i = toKeys_.lower_bound(c);
    for (; i != toKeys_.end() && i->second != key; ++i);
    if (i != toKeys_.end())
      toKeys_.erase(i);
    else
      LOG(ERROR) << "1: Couldn't remove key " << key;
  } else {
    LOG(ERROR) << "2: Couldn't remove key " << key;
  }
}

}  // namespacec command
}  // namespace rec

