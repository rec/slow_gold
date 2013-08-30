#include "rec/slow/commands/SlowCommandData.h"

#include "rec/command/CommandData.h"
#include "rec/slow/Menus.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/Binary.h"

namespace rec {
namespace slow {

using namespace rec::command;

namespace {

Commands makeCommand() {
  SlowCommands slowCommands = BINARY_PROTO(SlowCommands_def, SlowCommands);

  Commands commands;
  for (auto& slowCommand: slowCommands.slow_command()) {
    Command* command = commands.add_command();
    *command = slowCommand.command();
    command->set_type(static_cast<Command::Type>(slowCommand.type()));
  }
  return commands;
}

class SlowCommandData : public CommandData {
 public:
  explicit SlowCommandData(Instance* i)
      : update_(i->menus_.get()),
        allCommands_(makeCommand()) {
  }
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
