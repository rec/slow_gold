#include "rec/command/Command.h"
#include "rec/command/CommandDatabase.h"

namespace rec {
namespace command {

static CommandDatabase* commandDatabase() {
  static CommandDatabase d;
  return &d;
}

const CommandTable getCommands() { return commandDatabase()->commandTable(); }
void recalculate() { commandDatabase()->recalculate(); }

}  // namespace command
}  // namespace rec
