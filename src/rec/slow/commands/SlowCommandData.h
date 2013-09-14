#ifndef __REC_COMMAND_DATA_SLOWCOMMANDDATA__
#define __REC_COMMAND_DATA_SLOWCOMMANDDATA__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/util/Binary.h"

namespace rec {
namespace slow {

class Instance;

template <typename ProgramCommands>
command::Commands convertCommands() {
  ProgramCommands slowCommands = BINARY_PROTO(Commands, ProgramCommands);
  command::Commands commands;
  for (auto& slowCommand: slowCommands.command()) {
    command::Command* command = commands.add_command();
    *command = slowCommand.command();
    command->set_id(slowCommand.id());
  }
  return commands;
}

command::KeyStrokeCommandMapProto makeKeyBindings();

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_DATA_SLOWCOMMANDDATA__
