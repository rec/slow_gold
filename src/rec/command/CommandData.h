#ifndef __REC_COMMAND_DATA_SLOWCOMMANDDATA__
#define __REC_COMMAND_DATA_SLOWCOMMANDDATA__

#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/util/BinaryMacros.h"

namespace rec {
namespace command {

class Instance;

template <typename ProgramCommands>
Commands convertCommands() {
  ProgramCommands slowCommands = BINARY_PROTO(Commands, ProgramCommands);
  Commands commands;
  for (auto& slowCommand: slowCommands.command()) {
    Command* command = commands.add_command();
    *command = slowCommand.command();
    command->set_id(slowCommand.id());
  }
  return commands;
}

template <typename CommandMapProto>
KeyStrokeCommandMapProto convertKeyBindings() {
  CommandMapProto slowMaps = BINARY_PROTO(KeyStrokeMap, CommandMapProto);

  KeyStrokeCommandMapProto bindings;
  auto map = bindings.mutable_map();
  for (auto& slowEntry: slowMaps.entry()) {
    auto entry = map->add_entry();
    *entry = slowEntry.entry();
    entry->set_id(slowEntry.id());
  }
  return bindings;
}

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_DATA_SLOWCOMMANDDATA__
