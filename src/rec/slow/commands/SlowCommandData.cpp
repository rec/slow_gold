#include "rec/slow/commands/SlowCommandData.h"
#include "rec/slow/commands/SlowCommand.pb.h"
#include "rec/util/Binary.h"

namespace rec {
namespace slow {

using namespace rec::command;

Commands makeCommand() {
  SlowCommands slowCommands = BINARY_PROTO(SlowCommands, SlowCommands);

  Commands commands;
  for (auto& slowCommand: slowCommands.slow_command()) {
    Command* command = commands.add_command();
    *command = slowCommand.command();
    command->set_command(static_cast<slow::SlowCommand::Type>(slowCommand.type()));
  }
  return commands;
}

KeyStrokeCommandMapProto makeKeyBindings() {
  slow::SlowCommandMapProto slowMaps =
    BINARY_PROTO(SlowKeyStrokeMap, slow::SlowCommandMapProto);

  KeyStrokeCommandMapProto bindings;
  auto map = bindings.mutable_map();
  for (auto& slowEntry: slowMaps.slow_entry()) {
    auto entry = map->add_entry();
    *entry = slowEntry.entry();
    entry->set_command(slowEntry.command());
  }
  return bindings;
}

}  // namespace slow
}  // namespace rec
