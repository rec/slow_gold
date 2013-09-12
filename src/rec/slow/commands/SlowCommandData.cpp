#include "rec/slow/commands/SlowCommandData.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/Binary.h"

namespace rec {
namespace slow {

using namespace rec::command;

Commands makeCommand() {
  SlowCommands slowCommands = BINARY_PROTO(Commands, SlowCommands);

  Commands commands;
  for (auto& slowCommand: slowCommands.command()) {
    Command* command = commands.add_command();
    *command = slowCommand.command();
    command->set_id(slowCommand.id());
  }
  return commands;
}

KeyStrokeCommandMapProto makeKeyBindings() {
  slow::SlowCommandMapProto slowMaps =
    BINARY_PROTO(KeyStrokeMap, slow::SlowCommandMapProto);

  KeyStrokeCommandMapProto bindings;
  auto map = bindings.mutable_map();
  for (auto& slowEntry: slowMaps.entry()) {
    auto entry = map->add_entry();
    *entry = slowEntry.entry();
    entry->set_id(slowEntry.id());
  }
  return bindings;
}

}  // namespace slow
}  // namespace rec
