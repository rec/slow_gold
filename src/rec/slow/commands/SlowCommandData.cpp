#include "rec/slow/commands/SlowCommandData.h"
#include "rec/command/CommandData.h"
#include "rec/slow/HasInstance.h"
#include "rec/slow/Menus.h"
#include "rec/slow/callbacks/Callbacks.h"
#include "rec/slow/commands/Commands.def.h"
#include "rec/slow/commands/Descriptions.def.h"
#include "rec/slow/commands/KeyPresses.def.h"
#include "rec/slow/commands/Repeated.def.h"
#include "rec/slow/commands/Setters.def.h"

namespace rec {
namespace slow {

using command::Access;
using command::Commands;
using command::CommandData;

namespace {

class SlowCommandData : public CommandData, HasInstance {
 public:
  explicit SlowCommandData(Instance* i) : HasInstance(i), update_(menus()) {}
  const Commands& commands() const { return *commands::commands; }
  const Commands& descriptions(const Access&) const { return *commands::descriptions; }
  const Commands& keyPresses(const Access&) const { return *commands::keyPresses; }
  const Commands& repeated() const { return *commands::repeated; }
  const Commands& setters() const { return *commands::setters; }

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
