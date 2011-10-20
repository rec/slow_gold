#include "rec/command/Command.h"
#include "rec/command/data/CommandData.h"
#include "rec/command/Access.pb.h"
#include "rec/data/persist/Persist.h"
#include "rec/util/Defaulter.h"
#include "rec/util/STL.h"

namespace rec {
namespace command {

namespace {

enum MergeType { NEW, MERGE };

void merge(CommandTable* map, const Commands& commands, MergeType mergeType) {
  for (int i = 0; i < commands.command_size(); ++i) {
    const Command& cmd = commands.command(i);
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
}

class CommandDatabase {
 public:
  CommandDatabase() {
    recalculate();
  }

  ~CommandDatabase() {
    clear();
  }

  void clear() {
    stl::deleteMapPointers(&map_);
    map_.clear();
  }

  const Command command(Command::Type t) const {
    Lock l(lock_);

    CommandTable::const_iterator i = map_.find(t);
    return (i == map_.end()) ? Command::default_instance() : *(i->second);
  }

  const CommandTable commandTable() {
    Lock l(lock_);
    return map_;
  }

  void recalculate() {
    Lock l(lock_);
    Access access = data::get<Access>();
    clear();

    merge(&map_, commands(), NEW);
    merge(&map_, descriptions(access), MERGE);
    merge(&map_, keyPresses(access), MERGE);
  }

 private:
  CriticalSection lock_;
  CommandTable map_;

  DISALLOW_COPY_AND_ASSIGN(CommandDatabase);
};

CommandDatabase* commandDatabase() {
  static CommandDatabase d;
  return &d;
}

}  // namespace


// const Command getCommand(Command::Type t) { return commandDatabase()->command(t); }
const CommandTable getCommands() { return commandDatabase()->commandTable(); }
void recalculate() { commandDatabase()->recalculate(); }

}  // namespace command
}  // namespace rec
