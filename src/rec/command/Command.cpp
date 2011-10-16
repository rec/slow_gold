#include "rec/command/Command.h"
#include "rec/command/Access.pb.h"
#include "rec/data/persist/Persist.h"
#include "rec/util/Defaulter.h"
#include "rec/util/STL.h"

namespace rec {
namespace command {

namespace {

//Def<

class CommandDatabase {
 public:
  CommandDatabase() { recalculate(); }
  ~CommandDatabase() { clear(); }
  void clear() { stl::deleteMapPointers(&map_); map_.clear(); }

  const Command command(Command::Type t) const {
    Lock l(lock_);

    CommandTable::const_iterator i = map_.find(t);
    return (i == map_.end()) ? Command::default_instance() : *(i->second);
  }

  const CommandTable commands() {
    Lock l(lock_);
    return map_;
  }

  void recalculate() {
    Lock l(lock_);
    Access access = data::get<Access>();
    clear();
    readCommands();
    mergeDescriptions(access);
    mergeKeyPresses(access);
  }

 private:
  void readCommands() {
  }

  void mergeDescriptions(const Access& access) {
  }

  void mergeKeyPresses(const Access& access) {
  }

  CriticalSection lock_;
  CommandTable map_;

  DISALLOW_COPY_AND_ASSIGN(CommandDatabase);
};

CommandDatabase* commandDatabase() {
  static CommandDatabase d;
  return &d;
}

}  // namespace


const Command getCommand(Command::Type t) { return commandDatabase()->command(t); }
const CommandTable getCommands() { return commandDatabase()->commands(); }
void recalculate() { commandDatabase()->recalculate(); }

}  // namespace command
}  // namespace rec
