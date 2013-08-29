#include "rec/slow/commands/SlowCommandData.h"

#include "rec/command/CommandData.h"
#include "rec/slow/Menus.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/util/Binary.h"

namespace rec {
namespace slow {

using command::Commands;
using command::CommandData;

namespace {

class SlowCommandData : public CommandData {
 public:
  explicit SlowCommandData(Instance* i)
      : update_(i->menus_.get()),
        allCommands_(BINARY_PROTO(AllCommands_def, command::Commands)) {}
  const Commands& allCommands() const { return allCommands_; }

  virtual void addCallbacks(command::CallbackTable* table) const {
    addSlowCallbacks(table);
  }

  Listener<None>* getMenuUpdateListener() const { return update_; }

 private:
 	Listener<None>* update_;
  const command::Commands allCommands_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(SlowCommandData);
};

}  // namespace

CommandData* createSlowCommandData(Instance* i) { return new SlowCommandData(i); }

}  // namespace slow
}  // namespace rec
