// TODO: we can just refactor this out, it doesn't do anything any more.

#include "rec/slow/commands/SlowCommandData.h"
#include "rec/command/CommandData.h"
#include "rec/slow/HasInstance.h"
#include "rec/slow/Menus.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/AllCommands.def.h"

namespace rec {
namespace slow {

using command::Access;
using command::Commands;
using command::CommandData;

namespace {

class SlowCommandData : public CommandData, HasInstance {
 public:
  explicit SlowCommandData(Instance* i) : HasInstance(i), update_(menus()) {}
  const Commands& allCommands() const { return *commands::allCommands; }

  virtual void addCallbacks(command::CommandRecordTable* table) const {
    addSlowCallbacks(instance_, table);
  }

  Listener<None>* getMenuUpdateListener() const { return update_; }

 private:
 	Listener<None>* update_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SlowCommandData);
};

}  // namespace

CommandData* createSlowCommandData(Instance* i) { return new SlowCommandData(i); }

}  // namespace slow
}  // namespace rec
