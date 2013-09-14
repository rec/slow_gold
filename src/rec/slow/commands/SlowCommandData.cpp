#include "rec/slow/commands/SlowCommandData.h"
#include "rec/slow/commands/Command.pb.h"

namespace rec {
namespace slow {

command::Commands makeCommand() {
  slow::Commands slowCommands = BINARY_PROTO(Commands, slow::Commands);
  command::Commands commands;
  for (auto& slowCommand: slowCommands.command()) {
    command::Command* command = commands.add_command();
    *command = slowCommand.command();
    command->set_id(slowCommand.id());
  }
  return commands;
}

command::KeyStrokeCommandMapProto makeKeyBindings() {
  slow::CommandMapProto slowMaps =
    BINARY_PROTO(KeyStrokeMap, slow::CommandMapProto);

  command::KeyStrokeCommandMapProto bindings;
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
