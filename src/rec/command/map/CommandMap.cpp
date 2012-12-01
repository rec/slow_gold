#include "rec/command/map/CommandMap.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/Key.h"

namespace rec {
namespace command {

using namespace juce;

bool CommandMap::addKey(const string& key, CommandType command) {
  static const int RECENT = Command::RECENT_FILES;
  static const int BEGIN = CommandIDEncoder::toCommandID(RECENT, 11);
  static const int END = CommandIDEncoder::toCommandID(RECENT, 100);

  if (command >= BEGIN && command < END)
    return false;

  CommandIDEncoder enc = CommandIDEncoder::fromCommandID(command);
  bool exists = (toCommand_.find(key) != toCommand_.end());

  if (exists)
    beep();
  else
    toCommand_[key] = command;
  return !exists;
}

void CommandMap::addCommands(const CommandMapProto& commands) {
  toCommand_.clear();
  toKeys_.clear();
  for (int i = 0; i < commands.entry_size(); ++i) {
    const CommandMapEntry& entry = commands.entry(i);
    CommandType command = entry.command();
    for (int j = 0; j < entry.key_size(); ++j)
      add(entry.key(j), command);
  }
}

bool CommandMap::add(const string& key, CommandType command) {
  if (!addKey(key, command))
    return false;

  toKeys_[command].push_back(key);
  return true;
}

bool CommandMap::addAtIndex(const string& key, CommandType command, int index) {
  if (index < 0)
    add(key, command);

  if (!addKey(key, command))
    return false;

  toKeys_[command][index] = key;
  return true;
}

const CommandMapProto CommandMap::getProto() const {
  CommandMapProto commands;
  CommandToKeys::const_iterator i;
  for (i = toKeys_.begin(); i != toKeys_.end(); ++i) {
    if (!i->second.empty()) {
      CommandMapEntry* entry = commands.add_entry();
      entry->set_command(i->first);
      KeyVector::const_iterator j;
      for (j = i->second.begin(); j != i->second.end(); ++j)
        entry->add_key(*j);
    }
  }

  return commands;
}

bool CommandMap::invokeAsync(const string& key,
                             ApplicationCommandManager* acm) const {
  CommandID id = getCommand(key);
  return (id != command::Command::NONE) && acm->invokeDirectly(id, true);
}

CommandMap::CommandType CommandMap::getCommand(const string& key) const {
  KeyToCommand::const_iterator i = toCommand_.find(key);
  return (i == toCommand_.end()) ? command::Command::NONE : i->second;
}

const CommandMap::KeyVector& CommandMap::getKeys(CommandType c) const {
  CommandToKeys::const_iterator i = toKeys_.find(c);
  static const KeyVector empty;
  return (i != toKeys_.end()) ? i->second : empty;
}

void CommandMap::removeCommand(CommandType c, uint keyIndex) {
  CommandToKeys::iterator i = toKeys_.find(c);
  if (i == toKeys_.end()) {
    LOG(DFATAL) << "Couldn't remove message";
  } else if (i->second.size() <= keyIndex) {
    LOG(DFATAL) << "Couldn't find index " << keyIndex;
  } else {
    toCommand_.erase(i->second[keyIndex]);
    i->second.erase(i->second.begin() + keyIndex);
  }
}

void CommandMap::removeKey(const string& key) {
  if (CommandType c = getCommand(key)) {
    toCommand_.erase(key);
    CommandToKeys::iterator i = toKeys_.find(c);
    if (i == toKeys_.end()) {
      LOG(DFATAL) << "Couldn't remove message";
    } else {
      for (uint j = 0; j < i->second.size(); ++j) {
        if (i->second[j] == key) {
          i->second.erase(i->second.begin() + j);
          return;
        }
      }
    }
    LOG(DFATAL) << "Couldn't erase key " << key;
  }
}

void fillKeyPressMappingSet(const CommandMapProto& commandMap,
                            KeyPressMappingSet* mappings) {
  mappings->clearAllKeyPresses();
  for (int i = 0; i < commandMap.entry_size(); ++i) {
    const CommandMapEntry& m = commandMap.entry(i);
    for (int j = 0; j < m.key_size(); ++j)
      mappings->addKeyPress(m.command(), keyPressFromString(m.key(j)));
  }
}

}  // namespace command
}  // namespace rec

