#include "rec/audio/midi/CommandMap.h"

namespace rec {
namespace audio {
namespace midi {

void CommandMap::initialize(const CommandMapProto& commands) {
  map_.clear();
  for (int i = 0; i < commands.entry_size(); ++i) {
    const CommandMapEntry& entry = commands.entry(i);
    map_[entry.key()] = entry.command();
  }
}

const CommandMapProto CommandMap::getProto() const {
  CommandMapProto commands;
  for (Map::const_iterator i = map_.begin(); i != map_.end(); ++i) {
    CommandMapEntry* entry = commands.add_entry();
    entry->set_key(i->first);
    entry->set_command(i->second);
  }

  return commands;
}

command::Command::Type CommandMap::getCommand(const string& key) {
  Map::const_iterator i = map_.find(key);
  return (i == map_.end()) ? command::Command::NONE : i->second;
}

}  // namespace midi
}  // namespace audio
}  // namespace rec
