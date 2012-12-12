#include "rec/slow/commands/SlowCommandData.h"
#include "rec/command/CommandData.h"
#include "rec/slow/Menus.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/AllCommands.def.h"

namespace rec {
namespace slow {

using command::Access;
using command::Commands;
using command::CommandData;

namespace {

class SlowCommandData : public CommandData {
 public:
  explicit SlowCommandData(Instance* i) : update_(i->menus_.get()) {}
  const Commands& allCommands() const { return *commands::allCommands; }

  virtual void addCallbacks(command::CallbackTable* table) const {
    addSlowCallbacks(table);
  }

  Listener<None>* getMenuUpdateListener() const { return update_; }

 private:
 	Listener<None>* update_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowCommandData);
};

}  // namespace

CommandData* createSlowCommandData(Instance* i) { return new SlowCommandData(i); }

}  // namespace slow
}  // namespace rec
