#include "rec/command/CommandMap.h"

namespace rec {
namespace command {

void CommandMap::operator()(const CommandMapProto& commands) {
  toCommand_.clear();
  toKeys_.clear();
  for (int i = 0; i < commands.entry_size(); ++i) {
    const CommandMapEntry& entry = commands.entry(i);
    Command command = entry.command();
    for (int j = 0; j < entry.key_size(); ++j)
      add(entry.key(j), command);
  }
}

void CommandMap::add(const Key& key, Command command, int index) {
  // TODO:  check for dupes?
  toCommand_[key] = command;
  if (index == -1)
    toKeys_[command].push_back(key);
  else
    toKeys_[command][index] = key;
}

const CommandMapProto CommandMap::getProto() const {
  CommandMapProto commands;
  CommandToKeys::const_iterator i;
  for (i = toKeys_.begin(); i != toKeys_.end(); ++i) {
    CommandMapEntry* entry = commands.add_entry();
    entry->set_command(i->first);
    vector<Key>::const_iterator j;
    for (j = i->second.begin(); j != i->second.end(); ++j)
      entry->add_key(*j);
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

const vector<CommandMap::Key>& CommandMap::getKeys(Command c) const {
  CommandToKeys::const_iterator i = toKeys_.find(c);
  static vector<Key> empty;
  return (i != toKeys_.end()) ? i->second : empty;
}

void CommandMap::removeCommand(Command c, int keyIndex) {
  typedef CommandToKeys::iterator iterator;
  iterator i = toKeys_.find(c);
  if (i == toKeys_.end()) {
    LOG(ERROR) << "Couldn't remove message";
  } else if (i->second.size() <= keyIndex) {
    LOG(ERROR) << "Couldn't find index " << keyIndex;
  } else {
    toCommand_.erase(i->second[keyIndex]);
    i->second.erase(i->second.begin() + keyIndex);
  }
}

void CommandMap::removeKey(const Key& key) {
  typedef CommandToKeys::iterator iterator;
  if (Command c = getCommand(key)) {
    toCommand_.erase(key);
    iterator i = toKeys_.find(c);
    if (i == toKeys_.end()) {
      LOG(ERROR) << "Couldn't remove message";
    } else {
      for (int j = 0; j < i->second.size(); ++j) {
        if (i->second[j] == key) {
          i->second.erase(i->second.begin() + j);
          return;
        }
      }
    }
    LOG(ERROR) << "Couldn't erase key " << key;
  } else {
    LOG(ERROR) << "Couldn't find key " << key;
  }
}

}  // namespacec command
}  // namespace rec

