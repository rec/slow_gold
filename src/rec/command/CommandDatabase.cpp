#include "rec/command/CommandDatabase.h"
#include "rec/command/data/CommandData.h"
#include "rec/command/Access.pb.h"
#include "rec/data/persist/Persist.h"
#include "rec/util/Defaulter.h"
#include "rec/util/STL.h"

namespace rec {
namespace command {

namespace {

enum MergeType { NEW, MERGE };

void merge(CommandTable* map, const Command& cmd, MergeType mergeType) {
  const Command::Type type = cmd.type();
  CommandTable::iterator j = map->find(type);
  if (j == map->end()) {
    if (mergeType == NEW)
      map->insert(j, std::make_pair(type, new Command(cmd)));
    else
      LOG(ERROR) << "No existing command " << type;
  } else {
    if (mergeType == MERGE)
      j->second->MergeFrom(cmd);
    else
      LOG(ERROR) << "Can't replacing existing command " << type;
  }
}

void merge(CommandTable* map, const Commands& commands, MergeType mergeType) {
  for (int i = 0; i < commands.command_size(); ++i)
    merge(map, commands.command(i), mergeType);
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

void CommandDatabase::recalculate() {
  Lock l(lock_);
  Access access = data::get<Access>();
  clear();

  merge(&map_, commands(), NEW);
  merge(&map_, descriptions(access), MERGE);
  merge(&map_, keyPresses(access), MERGE);
}

}  // namespace command
}  // namespace rec
