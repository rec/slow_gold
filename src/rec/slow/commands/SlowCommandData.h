#ifndef __REC_COMMAND_DATA_SLOWCOMMANDDATA__
#define __REC_COMMAND_DATA_SLOWCOMMANDDATA__

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/util/Binary.h"

namespace rec {
namespace slow {

class Instance;

command::Commands makeCommand();

#if 0
template <typename ProgramCommands>
command::Commands makeCommand() {
  ProgramCommands programCommands = BINARY_PROTO(Commands, ProgramCommands);

  command::Commands commands;
  // typename
  for (auto& programCommand: programCommands.command()) {
    command::Command* command = commands.add_command();
    *command = programCommand.command();
    command->set_id(programCommand.id());
  }
  return commands;
}
#endif

command::KeyStrokeCommandMapProto makeKeyBindings();

}  // namespace slow
}  // namespace rec

#endif  // __REC_COMMAND_DATA_SLOWCOMMANDDATA__
