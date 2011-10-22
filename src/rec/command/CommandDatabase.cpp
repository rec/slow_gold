#include "rec/command/CommandDatabase.h"
#include "rec/slow/Position.h"
#include "rec/command/data/CommandData.h"
#include "rec/command/Access.pb.h"
#include "rec/data/persist/Persist.h"
#include "rec/util/Defaulter.h"
#include "rec/util/STL.h"

namespace rec {
namespace command {

namespace {

using slow::Position;

void insert(CommandTable* map, const Command& cmd, CommandID id = 0) {
  if (!id)
    id = cmd.type();

  // DLOG(INFO) << "Inserting " << Position::commandIDName(id);
  CommandTable::iterator j = map->find(id);
  if (j == map->end())
    map->insert(j, std::make_pair(id, new Command(cmd)));
  else
    LOG(ERROR) << "Can't replace " << Position::commandIDName(id);
}

void merge(CommandTable* map, const Command& cmd, CommandID id = 0) {
  if (!id)
    id = cmd.type();

  // DLOG(INFO) << "Merging " << Position::commandIDName(id) << ", " << id;
  CommandTable::iterator j = map->find(id);
  if (j != map->end())
    j->second->MergeFrom(cmd);
  else
    LOG(ERROR) << "No existing command " << Position::commandIDName(id);
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

static void mergeDescription(CommandTable* map, const Command& command) {
  static const char* LOWER[] = {" the first", " the previous", " the current",
                                " the next", " the last"};
  static const char* CAP[] = {" First", " Previous", " Current", " Next",
                              " Last"};

  CommandTable::iterator it = map->find(command.type());
  if (it != map->end()) {
    it->second->MergeFrom(command);
    return;
  }

  const String menu = str(command.desc().menu());
  const String full = str(command.desc().full());

  CommandID c = Command::BANK_SIZE * command.type();
  for (int i = Position::LAST; i <= Position::FIRST; ++i, ++c) {
    it = map->find(c);
    if (it == map->end()) {
      LOG(ERROR) << "Couldn't create position" << i
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

void CommandDatabase::recalculate() {
  Lock l(lock_);
  Access access = data::get<Access>();
  clear();

  for (int i = 0; i < commands().command_size(); ++i)
    insert(&map_, commands().command(i));

  for (int i = 0; i < repeated().command_size(); ++i) {
    const Command& command = repeated().command(i);
    Command c = command;

    // Insert each specific subcommand.
    for (int j = Position::FIRST; j < command.index(); ++j) {
      c.set_index(j);
      insert(&map_, c, Position::toCommandID(j, command.type()));
    }
  }

  const Commands& kp = keyPresses(access);
  for (int i = 0; i < kp.command_size(); ++i) {
    const Command& c = kp.command(i);
    merge(&map_, c, Position::toCommandID(c));
  }

  const Commands& desc = descriptions(access);
  for (int i = 0; i < desc.command_size(); ++i)
    mergeDescription(&map_, desc.command(i));
}

}  // namespace command
}  // namespace rec
