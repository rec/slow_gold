#include "rec/command/map/CommandMap.h"
#include "rec/slow/commands/Command.pb.h"

namespace rec {
namespace command {

using namespace juce;

bool CommandMap::addKey(const string& key, CommandID command) {
    static const CommandID RECENT = slow::Command::RECENT_FILES;
    static const CommandID BEGIN = RECENT + 11;
    static const CommandID END = RECENT + 100;

    if (command >= BEGIN && command < END) {
        DCHECK_EQ(command, 0);
        return false;
    }

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
    for (auto& entry: commands.entry()) {
        CommandID id = entry.id();
        for (auto& key: entry.key())
            add(key, id);
    }
}

void CommandMap::dump() const {
    for (auto& i: toKeys_) {
        DLOG(INFO) << i.first;
        for (auto& j: i.second)
            DLOG(INFO) << j;
    }
}

bool CommandMap::add(const string& key, CommandID id) {
    if (!addKey(key, id))
        return false;

    toKeys_[id].push_back(key);
    return true;
}

bool CommandMap::addAtIndex(const string& key, CommandID id, int index) {
    if (index < 0)
        add(key, id);

    if (!addKey(key, id))
        return false;

    toKeys_[id][index] = key;
    return true;
}

const CommandMapProto CommandMap::getProto() const {
    CommandMapProto commands;
    CommandToKeys::const_iterator i;
    for (i = toKeys_.begin(); i != toKeys_.end(); ++i) {
        if (!i->second.empty()) {
            CommandMapEntry* entry = commands.add_entry();
            CommandID id = i->first;
            CommandID index = id % Command::BANK_SIZE;

            entry->set_id(id - index);
            entry->set_index(index);
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
    return (id != slow::Command::NONE) && acm->invokeDirectly(id, true);
}

CommandID CommandMap::getCommand(const string& key) const {
    KeyToCommand::const_iterator i = toCommand_.find(key);
    return (i == toCommand_.end()) ? slow::Command::NONE : i->second;
}

const CommandMap::KeyVector& CommandMap::getKeys(CommandID c) const {
    CommandToKeys::const_iterator i = toKeys_.find(c);
    static const KeyVector empty;
    return (i != toKeys_.end()) ? i->second : empty;
}

void CommandMap::removeCommand(CommandID c, uint keyIndex) {
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
    if (CommandID c = getCommand(key)) {
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

}  // namespace command
}  // namespace rec
