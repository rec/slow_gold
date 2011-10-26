#include "rec/command/CommandDatabase.h"
#include "rec/command/Access.pb.h"
#include "rec/command/data/CommandData.h"
#include "rec/data/Data.h"
#include "rec/slow/Position.h"
#include "rec/util/Defaulter.h"
#include "rec/util/STL.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace command {

namespace {

using slow::Position;

enum MergeType {INSERT, MERGE};

void addTo(MergeType type, CommandTable* map, const Command& cmd,
           CommandID id = 0) {
  if (!id)
    id = Position::toCommandID(cmd);

  CommandTable::iterator j = map->find(id);
  if (j == map->end()) {
    if (type == INSERT)
      map->insert(j, std::make_pair(id, new Command(cmd)));
    else
    LOG(ERROR) << "No existing command " << Position::commandIDName(id);
  } else {
    if (type == MERGE)
      j->second->MergeFrom(cmd);
    else
      LOG(ERROR) << "Can't replace " << Position::commandIDName(id);
  }
}

void merge(CommandTable* map, const Command& cmd, CommandID id = 0) {
  addTo(MERGE, map, cmd, id);
}

void insert(CommandTable* map, const Command& cmd, CommandID id = 0) {
  addTo(INSERT, map, cmd, id);
}

}  // namespace

CommandDatabase::CommandDatabase() {
  recalculate();
}

CommandDatabase::~CommandDatabase() {
  clear();
}

void CommandDatabase::clear() {
  stl::deleteMapPointers(&map_);
  map_.clear();
}

const Command CommandDatabase::command(CommandID t) const {
  Lock l(lock_);

  CommandTable::const_iterator i = map_.find(t);
  return (i == map_.end()) ? Command::default_instance() : *(i->second);
}

const CommandTable CommandDatabase::commandTable() const {
  Lock l(lock_);
  return map_;
}

namespace {

void insertSingle(CommandTable* map) {
  for (int i = 0; i < commands().command_size(); ++i)
    insert(map, commands().command(i));
}

void insertRepeated(CommandTable* map) {
  for (int i = 0; i < repeated().command_size(); ++i) {
    const Command& command = repeated().command(i);
    Command c = command;

    // Insert each specific subcommand.
    for (int j = Position::FIRST; j < command.index(); ++j) {
      c.set_index(j);
      insert(map, c, Position::toCommandID(j, command.type()));
    }
  }
}

void mergeKeyPresses(CommandTable* map, const Access& access) {
  Commands kp = keyPresses(access);
  for (int i = 0; i < kp.command_size(); ++i) {
    const Command& c = kp.command(i);
    merge(map, c);
  }
}

void mergeDescription(CommandTable* map, const Command& command) {
  CommandTable::iterator it = map->find(command.type());
  if (it != map->end()) {
    it->second->MergeFrom(command);
    return;
  }

  static const char* LOWER[] = {" the first", " the previous", " the current",
                                " the next", " the last"};
  static const char* CAP[] = {" First", " Previous", " Current", " Next",
                              " Last"};

  const String menu = str(command.desc().menu());
  const String full = str(command.desc().full());

  CommandID c = Command::BANK_SIZE * command.type();
  for (int i = 0; i <= Position::LAST - Position::FIRST; ++i, ++c) {
    it = map->find(c);
    if (it == map->end()) {
      LOG(ERROR) << "Couldn't find position" << i
                 << " CommandID " << c
                 << " cmd: " << command.ShortDebugString();
      return;
    }
    Description* desc = it->second->mutable_desc();
    desc->set_menu(str(String::formatted(menu, CAP[i], "")));
    desc->set_full(str(String::formatted(full, LOWER[i], "")));
  }

  for (int i = 0; ; ++i, ++c) {
    it = map->find(c);
    if (it == map->end())
      break;

    String n = " " + String(i + 1);
    const char* s = n.toUTF8();
    Description* desc = it->second->mutable_desc();
    desc->set_menu(str(String::formatted(menu, "", s)));
    desc->set_full(str(String::formatted(full, "", s)));
  }
}

void mergeDescriptions(CommandTable* map, const Access& access) {
  const Commands& desc = descriptions(access);
  for (int i = 0; i < desc.command_size(); ++i)
    mergeDescription(map, desc.command(i));
}

void removeEmpties(CommandTable* map) {
  std::vector<CommandID> empties;
  for (CommandTable::const_iterator i = map->begin(); i != map->end(); ++i) {
    const Description& desc = i->second->desc();
    if (!(desc.menu().size() && desc.full().size())) {
      empties.push_back(i->first);
      LOG(ERROR) << "Removing empty command "
                 << Position::commandIDName(i->first);
    }
  }

  for (int i = 0; i < empties.size(); ++i)
    map->erase(empties[i]);
}

}  // namespace

void CommandDatabase::recalculate() {
  Lock l(lock_);
  Access access = data::get<Access>();
  clear();

  insertSingle(&map_);
  insertRepeated(&map_);
  mergeKeyPresses(&map_, access);
  mergeDescriptions(&map_, access);
  removeEmpties(&map_);
}

}  // namespace command
}  // namespace rec

